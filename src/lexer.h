#include <fstream>
#include <stdbool.h>
#include <string>

enum token_type {
  END,
  INVALID,
  NUMBER,
  IDENTIFIER,
  LPAREN,
  RPAREN,
  SEMICOLON,
  PRINT,
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

const Token_Literal literals[] = {
    {.text = "(", .type = token_type::LPAREN, .name = "left parenthesis"},
    {.text = ")", .type = token_type::RPAREN, .name = "right parenthesis"},
    {.text = ";", .type = token_type::SEMICOLON, .name = "semicolon"},
    {.text = "print", .type = token_type::PRINT, .name = "stdio print"},
};
#define literals_size sizeof(literals) / sizeof(Token_Literal)

std::string token_type_name(token_type type);

class Lexer {
public:
  Lexer(std::ifstream &file);
  Token next();

private:
  bool isSpace(char &ch);
  bool isIDstart(char &ch);
  bool isID(char &ch);
  std::string content;
  int size;
  int cursor;
};
