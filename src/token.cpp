#include "token.h"

const Token_Literal *token_type_literal(token_type type) {
  for (int i = 0; i < literals_size; i++) {
    if (literals[i].type == type)
      return &literals[i];
  }

  return nullptr;
}

std::string token_type_name(token_type type) {
  switch (type) {
  case NUMBER:
    return "number";
  case IDENTIFIER:
    return "identifier";
  case STRING:
    return "string";
  default:
    const Token_Literal *l = token_type_literal(type);
    if (l != nullptr) {
      return l->name;
    }
    break;
  }
  return "unknown token";
}

std::string token_lexeme(Token token) {
  std::string s;
  for (int i = 0; i < token.len; i++) {
    s += token.lexeme[i];
  }

  return s;
}
