#include <cstdio>
#include <fstream>
#include <iostream>

#include "lexer.h"
#include "parser.h"
#include "scanner.h"

using namespace std;

int main() {
  ifstream file("scripts/func_call.z");

  // Check if the file was opened successfully
  if (!file) {
    cout << "Unable to open file";
    return 1;
  }

  Lexer lexer(file);
  Scanner scanner(lexer);

  // print lex report
  // while (!scanner.atEnd()) {
  //   Token t = scanner.consume();
  //   std::printf("\'%.*s\': %s\n", t.len, t.lexeme,
  //               token_type_name(t.type).c_str());
  // }

  Parser parser(scanner);
  Node prg = parser.parse();

  std::cout << prg << std::endl;

  // Close the file
  file.close();
  return 0;
}
