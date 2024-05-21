#include <cctype>
#include <iostream>
#include <string>
#include <string_view>

#include "lexer.h"
#include "token.h"

Lexer::Lexer(std::ifstream &file) {
  cursor = 0;
  char ch;
  while (file.get(ch)) {
    std::cout << ch;
    content += ch;
    size += 1;
  }
  std::cout << std::endl;

  std::cout << "[INFO] Lex Report: " << size << " chars read" << std::endl;
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

  std::string_view _content = content;
  _content = _content.substr(cursor, content.size());
  for (auto &l : literals) {
    if (_content.compare(0, l.text.size(), l.text) != 0) {
      continue;
    }

    t.type = l.type;
    t.len = l.text.size();
    cursor += t.len;

    return t;
  }

  if (isdigit(content[cursor])) {
    t.type = token_type::NUMBER;
    while (cursor <= size && isdigit(content[cursor])) {
      cursor++;
      t.len++;
    }
  } else if (content[cursor] == '"') {
    t.type = token_type::STRING;

    // skip first quote
    cursor++;
    t.len++;

    // count chars in quotes
    while (cursor < size && content[cursor] != '"') {
      cursor++;
      t.len++;
    }

    // count last quote and move cursor past it
    cursor++;
    t.len++;
  } else if (isIDstart(content[cursor])) {
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
