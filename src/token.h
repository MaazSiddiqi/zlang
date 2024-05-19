#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

enum class token_type {
  END,
  INVALID,
  FUNC_DECL,
  RETURN,
  WHILE,
  IF,
  LET,
  MINUS,
  NUMBER,
  STRING,
  IDENTIFIER,
  LPAREN,
  RPAREN,
  LCURLY,
  RCURLY,
  COMMA,
  SEMICOLON,
  PRINT,
  PLUS,
  ASTERISK,
  SLASH,
  EQUAL,
  OR,
  AND,
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
const std::vector<Token_Literal> literals = {
    {.text = "(", .type = token_type::LPAREN, .name = "left parenthesis"},
    {.text = ")", .type = token_type::RPAREN, .name = "right parenthesis"},
    {.text = "{", .type = token_type::LCURLY, .name = "left curly brace"},
    {.text = "}", .type = token_type::RCURLY, .name = "right curly brace"},
    {.text = ";", .type = token_type::SEMICOLON, .name = "semicolon"},
    {.text = ",", .type = token_type::COMMA, .name = "comma"},
    {.text = "print", .type = token_type::PRINT, .name = "stdio print"},
    {.text = "let", .type = token_type::LET, .name = "let statement"},
    {.text = "return", .type = token_type::RETURN, .name = "return statement"},
    {.text = "while", .type = token_type::WHILE, .name = "while statement"},
    {.text = "if", .type = token_type::IF, .name = "while statement"},
    {.text = "fn",
     .type = token_type::FUNC_DECL,
     .name = "function declaration"},
    {.text = "+", .type = token_type::PLUS, .name = "plus"},
    {.text = "-", .type = token_type::MINUS, .name = "minus"},
    {.text = "*", .type = token_type::ASTERISK, .name = "asterisk"},
    {.text = "/", .type = token_type::SLASH, .name = "slash"},
    {.text = "=", .type = token_type::EQUAL, .name = "equal"},
    {.text = "||", .type = token_type::OR, .name = "logical or"},
    {.text = "&&", .type = token_type::AND, .name = "logical and"},
};

const Token_Literal *token_type_literal(token_type type);

// get string representation of token
std::string token_type_name(token_type type);

std::string token_lexeme(Token token);

#endif // !TOKEN_H
