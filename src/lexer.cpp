#include "lexer.h"
#include <iostream>
#include <string>

Lexer::Lexer(std::ifstream &file) {
  char ch;
  while (file.get(ch)) {
    std::cout << ch;
    content += ch;
    size += 1;
  }
  std::cout << std::endl;

  std::cout << "\n-----\nLex Report: " << size << " chars read" << std::endl;
};

Token Lexer::next() {
  Token t;
  return t;
};
