#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "scanner.h"

struct Node_Stmts {};
struct Node_Prg {
  Node_Stmts stmts;
};

class Parser {
public:
  Parser(Scanner &scan);
  ~Parser();

  Node parse();

private:
  Scanner &scan;
  Node_Prg parseProgram();
  Node_Stmts parseStmts();
  void throwUnexpected(Token &given, std::string expected);
};

#endif // PARSER_H
