#include <cctype>
#include <iostream>
#include <string>

#include "lexer.h"

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

void Lexer::trim_leading_whitespace() {
  // trim leading whitespace
  if (cursor < size && isSpace(content[cursor])) {
    cursor++;
  }
}

void Lexer::trim_until_char() {
  trim_leading_whitespace();

  // trim single line leading comments
  if (cursor + 1 < size && content[cursor] == '/' &&
      content[cursor + 1] == '/') {
    while (cursor < size && content[cursor] != '\n') {
      cursor++;
    }
    cursor++;
  }

  trim_leading_whitespace();

  if (cursor + 1 < size && content[cursor] == '/' &&
      content[cursor + 1] == ';') {
    // skip found '/;'
    cursor += 2;
    while (cursor + 1 < size && content[cursor] != ';' &&
           content[cursor + 1] != '/') {
      cursor++;
    }
    // skip found ';/'
    cursor += 2;
  }

  trim_leading_whitespace();
}

Token Lexer::next() {
  trim_until_char();

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

  for (int i = 0; i < literals_size; i++) {
    int _cursor = cursor;
    int j = 0;

    const Token_Literal &l = literals[i];

    while (_cursor < size && j < l.text.size()) {
      if (content[_cursor] != l.text[j])
        break;
      _cursor++;
      j++;
    }

    if (j == l.text.size()) {
      // found literal
      t.type = l.type;
      t.len = l.text.size();
      cursor += t.len;
      return t;
    }
  }

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

  return t;
};
