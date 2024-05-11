#include "token.h"

std::string token_type_name(token_type type) {
  switch (type) {
  case NUMBER:
    return "number";
  case IDENTIFIER:
    return "identifier";
  default:
    for (int i = 0; i < literals_size; i++) {
      if (literals[i].type == type)
        return literals[i].name;
    }
    break;
  }
  return "unknown token";
}
