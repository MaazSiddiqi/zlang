#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "scanner.h"
#include "token.h"

struct Node_Stmt {};
struct Node_Stmts {};
struct Node_Scope {
  Node_Stmts stmts;
};
struct Node_Prg {
  Node_Scope scope;
};

class Parser {
public:
  Parser(Scanner &scan);
  ~Parser();

  Node parse();

private:
  Scanner &scan;
  Node_Prg parseProgram();
  Node_Scope parseScope();
  Node_Stmts parseStmts();
  Node_Stmt parseStmt();

  void expectLiteral(token_type type);
  void throwUnexpected(Token &given, std::string expected);
};

#endif // PARSER_H
