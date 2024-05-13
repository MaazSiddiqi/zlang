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

Node_Stmts Parser::parseStmts() {
  Node_Stmts stmts;

  while (scan.peek().type != token_type::RCURLY) {
    scan.consume();
  }

  return stmts;
}

Node_Prg Parser::parseProgram() {
  std::cout << std::endl;
  std::cout << "=== Parsing program ===" << std::endl;

  Node_Prg prg;

  Token &t = scan.peek();

  if (scan.peek().type == token_type::END) {
    std::cout << token_type_name(t.type) << std::endl;
    printf("'%s'\n", t.lexeme);
    return prg;
  }

  if (t.type != token_type::FUNC_DECL) {
    throwUnexpected(t, "fn");
  }
  scan.consume();
  t = scan.peek();

  if (t.type != token_type::IDENTIFIER && token_lexeme(t) != "main") {
    throwUnexpected(t, "main");
  }
  scan.consume();
  t = scan.peek();

  if (t.type != token_type::LPAREN) {
    throwUnexpected(t, "(");
  }
  scan.consume();

  if (t.type != token_type::RPAREN) {
    throwUnexpected(t, ")");
  }
  scan.consume();

  if (t.type != token_type::LCURLY) {
    throwUnexpected(t, "{");
  }
  scan.consume();

  prg.stmts = parseStmts();

  if (t.type != token_type::RCURLY) {
    throwUnexpected(t, "}");
  }
  scan.consume();

  return prg;
}
