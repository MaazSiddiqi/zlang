#include <fstream>
#include <iostream>

#include "lexer.h"

using namespace std;

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
