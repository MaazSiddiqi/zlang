#include <cstdlib>
#include <iostream>

#include "parser.h"
#include "token.h"

Parser::Parser(Scanner &scan) : scan(scan) {}

Parser::~Parser() {}

std::string Parser::currTokenInfo() {
  std::string info;
  info += token_type_name(scan.peek().type);
  info += " ";
  info += token_lexeme(scan.peek());

  return info;
}

Node Parser::parse() { return parseProgram(); }

void Parser::throwUnexpected(Token &t, std::string expected) {
  std::cerr << "\033[31m"
            << "[ERROR] Unexpected token: '" << token_lexeme(t) << "' ("
            << token_type_name(t.type) << "), expected: '" << expected << "'"
            << "\033[0m" << std::endl;
  std::cerr << "\033[31m"
            << "[ERROR] Parse failed at token: " << currTokenInfo() << "\033[0m"
            << std::endl;
  std::cout << "[INFO] Aborting parse (ERROR)" << std::endl;
  exit(EXIT_FAILURE);
}

Token Parser::expectLiteral(token_type type) {
  Token &t = scan.peek();
  const Token_Literal *l = token_type_literal(type);

  if (l == nullptr) {
    throwUnexpected(t, "literal token");
  }

  if (t.type != type) {
    throwUnexpected(t, token_type_literal(type)->text);
  }

  return scan.consume();
}

Node Parser::parseTermExpr() {
  // FIRST: number | id | '('
  // FOLLOWS: ';' | ')'

  Node expr;

  switch (scan.peek().type) {
  case token_type::NUMBER:
  case token_type::IDENTIFIER:
    expr.addToken(scan.consume());
    break;
  case token_type::LPAREN:
    expr.addToken(expectLiteral(token_type::LPAREN));
    expr.addNode(parseExpr());
    expr.addToken(expectLiteral(token_type::RPAREN));
    break;
  default:
    throwUnexpected(scan.peek(), "valid expression");
    break;
  }

  return expr;
}

Node Parser::parseMultExpr() {
  // FIRST: number | id | '('
  // ?FOLLOWS: ';' | ')'

  Node expr;

  if (scan.peek().type == token_type::SEMICOLON ||
      scan.peek().type == token_type::RPAREN) {
    return expr;
  }

  expr.addNode(parseTermExpr());

  if (scan.peek().type == token_type::ASTERISK ||
      scan.peek().type == token_type::SLASH) {
    expr.addToken(scan.consume());
    expr.addNode(parseMultExpr());
  }

  return expr;
}

Node Parser::parseExpr() {
  // FIRST: number | id | '('
  // ?FOLLOWS: ';' | ')'

  Node expr;

  expr.addNode(parseMultExpr());

  switch (scan.peek().type) {
  case token_type::PLUS:
  case token_type::MINUS:
    expr.addToken(scan.consume());
    expr.addNode(parseExpr());
    break;
  default:
    break;
  }

  return expr;
}

Node Parser::parseArgs() {
  Node args;

  if (scan.peek().type == token_type::RPAREN) {
    return args;
  }

  args.addNode(parseExpr());

  while (scan.peek().type != token_type::RPAREN) {
    args.addToken(expectLiteral(token_type::COMMA));
    args.addNode(parseExpr());
  }

  return args;
}

Node Parser::parseCond() {
  Node cond;

  switch (scan.peek().type) {
  case token_type::LPAREN:
    cond.addToken(expectLiteral(token_type::LPAREN));
    cond.addNode(parseCond());
    cond.addToken(expectLiteral(token_type::RPAREN));
    break;
  default:
    cond.addNode(parseExpr());

    switch (scan.peek().type) {
    case token_type::EQUAL:
      cond.addToken(expectLiteral(token_type::EQUAL));
      cond.addToken(expectLiteral(token_type::EQUAL));
      break;
    case token_type::GT:
      cond.addToken(expectLiteral(token_type::GT));
      if (scan.peek().type == token_type::EQUAL) {
        cond.addToken(expectLiteral(token_type::EQUAL));
      }
      break;
    case token_type::LT:
      cond.addToken(expectLiteral(token_type::LT));
      if (scan.peek().type == token_type::EQUAL) {
        cond.addToken(expectLiteral(token_type::EQUAL));
      }
      break;
    case token_type::NOT:
      cond.addToken(expectLiteral(token_type::NOT));
      cond.addToken(expectLiteral(token_type::EQUAL));
      break;
    default:
      throwUnexpected(scan.peek(), "valid comparator operator");
      break;
    }

    cond.addNode(parseExpr());
    break;
  }

  return cond;
}

Node Parser::parseConds() {
  Node conds;

  switch (scan.peek().type) {
  case token_type::LPAREN:
    conds.addToken(expectLiteral(token_type::LPAREN));
    conds.addNode(parseConds());
    conds.addToken(expectLiteral(token_type::RPAREN));
    break;
  default:
    conds.addNode(parseCond());

    while (scan.peek().type != token_type::RPAREN) {
      switch (scan.peek().type) {
      case token_type::OR:
        conds.addToken(expectLiteral(token_type::OR));
        break;
      case token_type::AND:
        conds.addToken(expectLiteral(token_type::AND));
        break;
      default:
        throwUnexpected(scan.peek(), "valid logical operator");
        break;
      }

      conds.addNode(parseConds());
    }

    break;
  }
  return conds;
}

Node Parser::parseStmt() {
  // FIRST: 'fn' | 'while' | 'if' | 'let' | id | 'return' | number | '('
  // FOLLOWS: 'fn' | 'while' | 'if' | 'let' | id | 'return' | number | '(' |
  // '}'

  Node stmt;

  switch (scan.peek().type) {
  case token_type::FUNC_DECL:
    stmt.addToken(expectLiteral(token_type::FUNC_DECL));

    if (scan.peek().type != token_type::IDENTIFIER) {
      throwUnexpected(scan.peek(), "valid identifier");
    }
    stmt.addToken(scan.consume());

    stmt.addToken(expectLiteral(token_type::LPAREN));
    stmt.addNode(parseArgs());
    stmt.addToken(expectLiteral(token_type::RPAREN));

    stmt.addNode(parseScope());
    break;
  case token_type::WHILE:
    stmt.addToken(expectLiteral(token_type::WHILE));

    stmt.addToken(expectLiteral(token_type::LPAREN));
    stmt.addNode(parseConds());
    stmt.addToken(expectLiteral(token_type::RPAREN));

    stmt.addNode(parseScope());
    break;
  case token_type::IF:
    stmt.addToken(expectLiteral(token_type::IF));

    stmt.addToken(expectLiteral(token_type::LPAREN));
    stmt.addNode(parseConds());
    stmt.addToken(expectLiteral(token_type::RPAREN));

    stmt.addNode(parseScope());
    break;
  case token_type::LET:
    stmt.addToken(expectLiteral(token_type::LET));

    if (scan.peek().type != token_type::IDENTIFIER) {
      throwUnexpected(scan.peek(), "valid identifier");
    }
    stmt.addToken(scan.consume());

    stmt.addToken(expectLiteral(token_type::EQUAL));
    stmt.addNode(parseExpr());
    stmt.addToken(expectLiteral(token_type::SEMICOLON));
    break;
  case token_type::IDENTIFIER:
  case token_type::NUMBER:
  case token_type::LPAREN:
    stmt.addNode(parseExpr());
    stmt.addToken(expectLiteral(token_type::SEMICOLON));
    break;
  case token_type::RETURN:
    stmt.addToken(expectLiteral(token_type::RETURN));
    stmt.addNode(parseExpr());
    stmt.addToken(expectLiteral(token_type::SEMICOLON));
    break;
  case token_type::SEMICOLON:
    stmt.addToken(expectLiteral(token_type::SEMICOLON));
    break;
  default:
    throwUnexpected(scan.peek(), "valid statement");
    break;
  }

  return stmt;
}

Node Parser::parseStmts() {
  // FIRST: 'fn' | 'while' | 'if' | id | 'return' | number | '('
  // FOLLOWS: '}'

  Node stmts;

  while (scan.peek().type != token_type::RCURLY) {
    stmts.addNode(parseStmt());
  }

  return stmts;
}

Node Parser::parseScope() {
  // FIRST: '{'
  // FOLLOWS: 'EOF' | '{'

  Node scope;

  scope.addToken(expectLiteral(token_type::LCURLY));
  scope.addNode(parseStmts());
  scope.addToken(expectLiteral(token_type::RCURLY));

  return scope;
}

Node Parser::parseProgram() {
  std::cout << std::endl;
  std::cout << "[INFO] Parsing program" << std::endl;

  Node prg;

  prg.addToken(expectLiteral(token_type::FUNC_DECL));

  if (scan.peek().type != token_type::IDENTIFIER ||
      token_lexeme(scan.peek()) != "main") {
    throwUnexpected(scan.peek(), "main");
  }
  prg.addToken(scan.consume());

  prg.addToken(expectLiteral(token_type::LPAREN));
  prg.addToken(expectLiteral(token_type::RPAREN));
  prg.addNode(parseScope());

  std::cout << "[INFO] Completed parse successfully" << std::endl;
  return prg;
}
