#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "parser.h"
#include "token.h"

Parser::Parser(Scanner &scan) : scan(scan) {}

Parser::~Parser() {}

Node Parser::parse() {
  Node x;
  parseProgram();
  return x;
}

void Parser::throwUnexpected(Token &t, std::string expected) {
  std::cerr << "Unexpected token: '" << token_lexeme(t) << "', expected: '"
            << expected << "'" << std::endl;
  std::cout << "=== Aborting parse (ERROR) ===" << std::endl;
  exit(EXIT_FAILURE);
}

void Parser::expectLiteral(token_type type) {
  Token &t = scan.peek();
  const Token_Literal *l = token_type_literal(type);

  if (l == nullptr) {
    throwUnexpected(t, "literal token");
  }

  if (t.type != type) {
    throwUnexpected(t, token_type_literal(type)->text);
  }

  scan.consume();
}

Node_Stmt Parser::parseStmt() {
  Node_Stmt stmt;

  return stmt;
}

Node_Stmts Parser::parseStmts() {
  Node_Stmts stmts;

  while (scan.peek().type != token_type::RCURLY) {
    scan.consume();
  }

  return stmts;
}

Node_Scope Parser::parseScope() {
  Node_Scope scope;
  Token &t = scan.peek();

  expectLiteral(token_type::LCURLY);

  scope.stmts = parseStmts();

  expectLiteral(token_type::RCURLY);

  return scope;
}

Node_Prg Parser::parseProgram() {
  std::cout << std::endl;
  std::cout << "=== Parsing program ===" << std::endl;

  Node_Prg prg;

  if (scan.peek().type == token_type::END) {
    printf("'%s'\n", scan.peek().lexeme);
    return prg;
  }

  expectLiteral(token_type::FUNC_DECL);

  if (scan.peek().type != token_type::IDENTIFIER && token_lexeme(t) != "main") {
    throwUnexpected(scan.peek(), "main");
  }
  scan.consume();

  expectLiteral(token_type::LPAREN);
  expectLiteral(token_type::RPAREN);

  prg.scope = parseScope();

  return prg;
}
