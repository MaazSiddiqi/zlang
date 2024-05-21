# zlang

## Overview

`zlang` is a custom programming language developed as an exploratory project around programming language development. This project aims to implement a complete language utilizing LLVM as a backend. The compiler will compile `zlang` code to LLVM Intermediate Representation (IR) Code, which LLVM can take to further optimize and build binaries on multiple architectures.

The goal is to build an interpretor for the language in the future as well.

### Grammar

Here is the grammar that I aim to implement.

```
program                -> fn main() scope EOF
scope                  -> {stmts}
stmts                  -> stmt stmts
stmts                  -> ϵ
stmt                   -> func_decl
stmt                   -> scope
stmt                   -> while_stmt
stmt                   -> if_stmt
stmt                   -> let id = expr;
stmt                   -> return expr;
stmt                   -> expr;
stmt                   -> ;
stmt                   -> ϵ
func_decl              -> fn id(args) scope
while_stmt             -> while (conditions) scope
if_stmt                -> if (conditions) scope if_tail
if_tail                -> elsif (conditions) scope if_tail
if_tail                -> else scope
if_tail                -> ϵ
expr                   -> add_expr
expr                   -> ϵ
add_expr               -> mult_expr '+' add_expr
add_expr               -> mult_expr '-' add_expr
add_expr               -> mult_expr
mult_expr              -> term_expr '*' mult_expr
mult_expr              -> term_expr '/' mult_expr
mult_expr              -> term_expr
term_expr              -> number
term_expr              -> id
term_expr              -> (expr)
conditions             -> condition conditions_tail
conditions             -> (conditions)
conditions_tail        -> lop conditions
conditions_tail        -> ϵ
condition              -> expr cmp expr
condition              -> (condition)
args                   -> id args_tail
args_tail              -> , id args_tail
args_tail              -> ϵ
op                     -> '+' | '-' | '*' | '/'
lop                    -> '||' | '&&'
cmp                    -> '<' | '>' | '<=' | '>=' | '==' | '!='
```

## Progress

Currently, I have completed the tokenizing and lexical analysis phase of the `zlang` development. I am now focusing on the semantic analysis and building the Abstract Syntax Tree (AST) for the language.

Semantic Productions Implemented:

- [x] Program
- [x] Statements
- [x] Function Declarations
- [x] While Loops
- [ ] If Statements
- [x] Expressions
- [x] Conditions
- [x] Arguments
- [x] Algebra/Comparison/Logic Operators

## Roadmap

The roadmap for the `zlang` project includes the following milestones:

1. Tokenizing `zlang` scripts and performing lexical analysis.
2. Implementing the parser to generate the AST.
3. **[Current]** Constructing the Abstract Syntax Tree (AST)
4. Decorating AST with LLVM IR Code.
5. Generating Binary through `llvm`
6. Testing and debugging the language implementation to ensure correctness and reliability.
7. Documenting the language specification, usage, and examples.
