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
  std::cerr << "[ERROR] Unexpected token: '" << token_lexeme(t)
            << "', expected: '" << expected << "'" << std::endl;
  std::cout << "[INFO] Aborting parse (ERROR)" << std::endl;
  std::cerr << "[ERROR] Parse failed at token: " << currTokenInfo()
            << std::endl;
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

  if (scan.peek().type == token_type::SEMICOLON ||
      scan.peek().type == token_type::RPAREN) {
    return expr;
  }

  expr.addNode(parseMultExpr());

  if (scan.peek().type == token_type::PLUS ||
      scan.peek().type == token_type::MINUS) {
    expr.addToken(scan.consume());
    expr.addNode(parseExpr());
  }

  return expr;
}

Node Parser::parseStmt() {
  // FIRST: 'fn' | 'while' | 'if' | 'let' | id | 'return' | number | '('
  // FOLLOWS: 'fn' | 'while' | 'if' | 'let' | id | 'return' | number | '(' | '}'

  Node stmt;

  switch (scan.peek().type) {
    // case FUNC_DECL:
    //   break;
    // case WHILE:
    //   break;
    // case IF:
    //   break;
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
