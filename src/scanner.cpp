#include "scanner.h"
#include "token.h"

Scanner::Scanner(Lexer &lexer) : lexer(lexer) { curr = lexer.next(); }

Scanner::~Scanner() {}

Token &Scanner::peek() { return curr; }
Token Scanner::consume() {
  Token res = curr;
  curr = lexer.next();
  return res;
}

bool Scanner::atEnd() { return curr.type == token_type::END; }
