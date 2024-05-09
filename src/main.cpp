#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Lexer {
public:
  Lexer(ifstream &file);
  ~Lexer();

private:
};

class Token {
  enum class Type {
    LParen,
    RParen,
    SemiColon,
    Plus,
    Minus,
    Asterisk,
    Slash,
    Number,
    Identifier,
    Unexpected,
  }

  Token(Type _type): type(_type) {}
  Token(Type _type, string _lexeme): type(_type) lexeme(_lexeme) {}
private:
  Type type;
  string lexeme;
}
  

Lexer ::Lexer(ifstream &file) {
  // Read the file character by character
  char ch;
  Token token;
  while (file.get(ch)) {
    cout << ch << " ";

    switch (ch) {
    case '(':
      cout << "found opening paren";
      break;
    case ')':
      cout << "found closing paren";
      break;
    case ';':
      cout << "ending statment";
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      cout << "found binop";
      break;
    default:
      if (isdigit(ch)) {
        cout << "Found digit";
      } else if (isalpha(ch)) {
        cout << "Found literal";
      }
      break;
    }
    cout << endl;
  }
  cout << endl;
}

Lexer ::~Lexer() {}

int main() {
  ifstream file("../scripts/print.z");

  // Check if the file was opened successfully
  if (!file) {
    cout << "Unable to open file";
    return 1;
  }

  Lexer lexer(file);

  // Close the file
  file.close();
  return 0;
}
