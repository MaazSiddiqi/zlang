#include <fstream>
#include <string>

enum token_type {
  END,
  INVALID,
  INT,
  STRING,
  LPAREN,
  RPAREN,
  SEMICOLON,
  KEYWORD,
};

class Token {
public:
  Token(){};
  ~Token(){};

private:
  token_type type;
  std::string lexeme;
};

class Lexer {
public:
  Lexer(std::ifstream &file);
  Token next();

private:
  std::string content;
  int size;
  int cursor;
};
