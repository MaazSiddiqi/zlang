#include <cstdio>
#include <fstream>
#include <iostream>

#include "lexer.h"
#include "parser.h"
#include "scanner.h"

using namespace std;

/*
 * === Grammer ===
 * program                -> fn main() scope EOF
 * scope                  -> {stmts}
 * stmts                  -> stmt stmts
 * stmts                  -> ϵ
 * stmt                   -> func_decl
 * stmt                   -> scope
 * stmt                   -> while_stmt
 * stmt                   -> if_stmt
 * stmt                   -> let id = expr;
 * stmt                   -> return expr;
 * stmt                   -> expr;
 * stmt                   -> ;
 * stmt                   -> ϵ
 * func_decl              -> fn id(args) scope
 * while_stmt             -> while (conditions) scope
 * if_stmt                -> if (conditions) scope if_tail
 * if_tail                -> elsif (conditions) scope if_tail
 * if_tail                -> else scope
 * if_tail                -> ϵ
 * expr                   -> add_expr
 * expr                   -> ϵ
 * add_expr               -> mult_expr '+' add_expr
 * add_expr               -> mult_expr '-' add_expr
 * add_expr               -> mult_expr
 * mult_expr              -> term_expr '*' mult_expr
 * mult_expr              -> term_expr '/' mult_expr
 * mult_expr              -> term_expr
 * term_expr              -> number
 * term_expr              -> id
 * term_expr              -> (expr)
 * conditions             -> condition conditions_tail
 * conditions_tail        -> lop conditions
 * conditions_tail        -> ϵ
 * condition              -> expr cmp expr
 * args                   -> id args_tail
 * args_tail              -> , id args_tail
 * args_tail              -> ϵ
 * op                     -> '+' | '-' | '*' | '/'
 * lop                    -> '||' | '&&'
 * cmp                    -> '<' | '>' | '<=' | '>=' | '==' | '!='
 */

int main() {
  ifstream file("../scripts/sample.z");

  // Check if the file was opened successfully
  if (!file) {
    cout << "Unable to open file";
    return 1;
  }

  Lexer lexer(file);
  Scanner scanner(lexer);

  // // print lex report
  // while (!scanner.atEnd()) {
  //   Token t = scanner.consume();
  //   std::printf("\'%.*s\': %s\n", t.len, t.lexeme,
  //               token_type_name(t.type).c_str());
  // }
  //
  Parser parser(scanner);
  Node prg = parser.parse();

  std::cout << prg << std::endl;

  // Close the file
  file.close();
  return 0;
}
