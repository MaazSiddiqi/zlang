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

Node Parser::parseStmt() {
  Node stmt;

  return stmt;
}

Node Parser::parseStmts() {
  Node stmts;

  while (scan.peek().type != token_type::RCURLY) {
    scan.consume();
  }

  return stmts;
}

Node Parser::parseScope() {
  Node scope;
  Token &t = scan.peek();

  expectLiteral(token_type::LCURLY);

  parseStmts();

  expectLiteral(token_type::RCURLY);

  return scope;
}

Node Parser::parseProgram() {
  std::cout << std::endl;
  std::cout << "=== Parsing program ===" << std::endl;

  Node prg;

  if (scan.peek().type == token_type::END) {
    printf("'%s'\n", scan.peek().lexeme);
    return prg;
  }

  expectLiteral(token_type::FUNC_DECL);

  if (scan.peek().type != token_type::IDENTIFIER ||
      token_lexeme(scan.peek()) != "main") {
    throwUnexpected(scan.peek(), "main");
  }
  scan.consume();

  expectLiteral(token_type::LPAREN);
  expectLiteral(token_type::RPAREN);

  Node scope = parseScope();

  return prg;
}