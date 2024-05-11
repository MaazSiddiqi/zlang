#include <cstdio>
#include <format>
#include <fstream>
#include <iostream>

#include "lexer.h"

using namespace std;

std::string token_type_name(token_type type) {
  std::string name;

  switch (type) {
  case END:
    name = "End of file";
    break;
  case INVALID:
    name = "Invalid token";
    break;
  case NUMBER:
    name = "Number";
    break;
  case IDENTIFIER:
    name = "Identifier";
    break;
  case LPAREN:
    name = "Left parenthesis";
    break;
  case RPAREN:
    name = "Rigth parenthesis";
    break;
  case SEMICOLON:
    name = "Semicolon";
    break;
  case KEYWORD:
    name = "Keyword";
    break;
  default:
    name = "Unreachable";
  }

  return name;
}

int main() {
  ifstream file("../scripts/print.z");

  // Check if the file was opened successfully
  if (!file) {
    cout << "Unable to open file";
    return 1;
  }

  Lexer lexer(file);

  Token t = lexer.next();
  while (t.type != token_type::END) {
    std::printf("%s: \'%.*s\'\n", token_type_name(t.type).c_str(), t.len,
                t.lexeme);
    t = lexer.next();
  }

  // Close the file
  file.close();
  return 0;
}
