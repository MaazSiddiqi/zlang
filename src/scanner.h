#ifndef SCANNER_H
#define SCANNER_H

#include "lexer.h"

class Scanner {
public:
  Scanner(Lexer &lexer);
  ~Scanner();

  Token &peek();
  Token consume();

  bool atEnd();

private:
  Lexer &lexer;
  Token curr;
};

#endif // !SCANNER_H
