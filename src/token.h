#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum token_type {
  END,
  INVALID,
  NUMBER,
  STRING,
  IDENTIFIER,
  LPAREN,
  RPAREN,
  LCURLY,
  RCURLY,
  SEMICOLON,
  PRINT,
  PLUS,
  MINUS,
  ASTERISK,
  SLASH,
  EQUAL,
};

struct Token_Literal {
  std::string text;
  token_type type;
  std::string name;
};

struct Token {
  token_type type;
  char *lexeme;
  int len;
};

// list of constant tokens
const Token_Literal literals[] = {
    {.text = "(", .type = token_type::LPAREN, .name = "left parenthesis"},
    {.text = ")", .type = token_type::RPAREN, .name = "right parenthesis"},
    {.text = "{", .type = token_type::LCURLY, .name = "left curly brace"},
    {.text = "}", .type = token_type::RCURLY, .name = "right curly brace"},
    {.text = ";", .type = token_type::SEMICOLON, .name = "semicolon"},
    {.text = "print", .type = token_type::PRINT, .name = "stdio print"},
    {.text = "+", .type = token_type::PLUS, .name = "plus"},
    {.text = "-", .type = token_type::MINUS, .name = "minus"},
    {.text = "*", .type = token_type::ASTERISK, .name = "asterisk"},
    {.text = "/", .type = token_type::SLASH, .name = "slash"},
    {.text = "=", .type = token_type::EQUAL, .name = "equal"},
};
#define literals_size sizeof(literals) / sizeof(Token_Literal)

// get string representation of token
std::string token_type_name(token_type type);

#endif // !TOKEN_H
