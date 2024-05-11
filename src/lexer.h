#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <stdbool.h>
#include <string>

#include "token.h"

class Lexer {
public:
  Lexer(std::ifstream &file);

  // get next token in file
  Token next();

private:
  // contents of file currently parsing
  std::string content;

  // size of file currently parsing
  int size;

  // position in file during lexing
  int cursor;

  // check if char is a space-like character
  bool isSpace(char &ch);

  // check if char is the start of a valid identifier
  bool isIDstart(char &ch);

  // check if char is part of a valid identifier
  bool isID(char &ch);

  // trim leading whitespace at cursor
  void trim_leading_whitespace();

  // trim comments and whitespace until next processable char
  void trim_until_char();
};

#endif // !LEXER_H
