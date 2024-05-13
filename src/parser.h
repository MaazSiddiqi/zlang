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
 * stmt                   -> expr;
 * stmt                   -> ϵ
 * func_decl              -> fn id(args) scope
 * while_stmt             -> while (conditions) scope
 * if_stmt                -> if (conditions) scope if_tail
 * if_tail                -> elsif (conditions) scope if_tail
 * if_tail                -> else scope
 * if_tail                -> ϵ
 * expr                   -> id = expr
 * expr                   -> return expr;
 * expr                   -> add_expr
 * expr                   -> ϵ
 * add_expr               -> mult_expr '+' add_expr
 * add_expr               -> mult_expr '-' add_expr
 * add_expr               -> mult_expr
 * mult_expr              -> term_expr '*' mult_expr
 * mult_expr              -> term_expr '/' mult_expr
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

#include "scanner.h"

struct Node_Prg {};

class Parser {
public:
  Parser(Scanner &scan);
  ~Parser();

private:
  Scanner &scan;
  Node_Prg parseProgram();
};
