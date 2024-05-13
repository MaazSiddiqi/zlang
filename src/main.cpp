#include <cstdio>
#include <fstream>
#include <iostream>

#include "lexer.h"
#include "scanner.h"

using namespace std;

int main() {
  ifstream file("../scripts/sample.z");

  // Check if the file was opened successfully
  if (!file) {
    cout << "Unable to open file";
    return 1;
  }

  Lexer lexer(file);
  Scanner scanner(lexer);

  // print lex report
  while (!scanner.atEnd()) {
    Token t = scanner.consume();
    std::printf("%s: \'%.*s\'\n", token_type_name(t.type).c_str(), t.len,
                t.lexeme);
  }

  // Close the file
  file.close();
  return 0;
}
