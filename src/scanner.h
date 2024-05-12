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
