#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "scanner.h"
#include "token.h"

class Parser {
public:
  Parser(Scanner &scan);
  ~Parser();

  Node parse();

private:
  Scanner &scan;
  Node parseProgram();
  Node parseScope();
  Node parseStmts();
  Node parseStmt();
  Node parseArgs();
  Node parseExpr();
  Node parseMultExpr();
  Node parseTermExpr();

  Token expectLiteral(token_type type);
  void throwUnexpected(Token &given, std::string expected);

  std::string currTokenInfo();
};

#endif // PARSER_H
