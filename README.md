# zlang

## Overview

`zlang` is a custom programming language developed as an exploratory project around programming language development. This project aims to implement a complete language from scratch, starting with lexing and scanning the token file to tokens.

### Grammar

Here is the grammar that I aim to implement.

```
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
* conditions             -> (conditions)
* conditions_tail        -> lop conditions
* conditions_tail        -> ϵ
* condition              -> expr cmp expr
* condition              -> (condition)
* args                   -> id args_tail
* args_tail              -> , id args_tail
* args_tail              -> ϵ
* op                     -> '+' | '-' | '*' | '/'
* lop                    -> '||' | '&&'
* cmp                    -> '<' | '>' | '<=' | '>=' | '==' | '!='
```

## Progress

At this stage, the lexing and scanning of the token file to tokens has been completed. The grammar for the language has been written, and the next step is to write a parser for it. Following that, the plan is to construct the Abstract Syntax Tree (AST), decorate it, and continue with the backend development of the language.

## Roadmap

The roadmap for the `zlang` project includes the following milestones:

1. Implementing the parser to generate the AST.
2. Constructing the Abstract Syntax Tree (AST) and decorating it with additional information.
3. Developing the backend of the language, including code generation and optimization.
4. Adding support for additional language features, such as control flow statements, functions, and data types.
5. Testing and debugging the language implementation to ensure correctness and reliability.
6. Documenting the language specification, usage, and examples.
