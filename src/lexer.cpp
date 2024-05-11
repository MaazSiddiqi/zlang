#include "lexer.h"
#include <cctype>
#include <iostream>
#include <string>

Lexer::Lexer(std::ifstream &file) {
  cursor = 0;
  char ch;
  while (file.get(ch)) {
    std::cout << ch;
    content += ch;
    size += 1;
  }
  std::cout << std::endl;

  std::cout << "\n-----\nLex Report: " << size << " chars read" << std::endl;
};

bool Lexer::isSpace(char &ch) {
  switch (ch) {
  case ' ':
  case '\n':
  case '\t':
    return true;
    break;
  default:
    return false;
  }
};

bool Lexer::isIDstart(char &ch) { return isalpha(ch) || ch == '_'; }
bool Lexer::isID(char &ch) { return isalnum(ch) || ch == '_'; }

Token Lexer::next() {
  // trim leading whitespace
  if (cursor < size && isSpace(content[cursor])) {
    cursor++;
  }

  Token t = {
      .type = token_type::END,
      .lexeme = &content[size],
      .len = 0,
  };

  if (cursor >= size) {
    return t;
  }

  t.lexeme = &content[cursor]; // ch
  char ch = content[cursor];

  switch (ch) {
  case '(':
    t.type = token_type::RPAREN;
    t.len = 1;
    cursor++;
    break;
  case ')':
    t.type = token_type::LPAREN;
    t.len = 1;
    cursor++;
    break;
  case ';':
    t.type = token_type::SEMICOLON;
    t.len = 1;
    cursor++;
    break;
  default:
    if (isdigit(ch)) {
      t.type = token_type::NUMBER;

      while (cursor <= size && isdigit(content[cursor])) {
        cursor++;
        t.len++;
      }
    } else if (isIDstart(ch)) {
      t.type = token_type::IDENTIFIER;

      while (cursor <= size && isID(content[cursor])) {
        cursor++;
        t.len++;
      }
    } else {
      t.type = token_type::INVALID;
      t.len = 1;
      cursor++;
    }
    break;
  }

  return t;
};
