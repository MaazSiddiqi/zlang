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
  KEYWORD,
};

struct Token {
  token_type type;
  char *lexeme;
  int len;
};

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
