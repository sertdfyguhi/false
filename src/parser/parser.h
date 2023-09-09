#ifndef PARSER_H
#define PARSER_H

#include "../error.h"
#include "../lexer/token.h"
#include "nodes.h"

#include <stdio.h>
#include <stdlib.h>

int parse(Token* tokens, size_t tsize, Node** nodes_ptr, size_t* nsize_ptr, Error* err_ptr);
int parse_assign(Token* tokens, size_t* i, Node* ast_ptr, Error* err_ptr);
int parse_block(NodeType type, Token* tokens, size_t* i, Node* ast_ptr, Error* err_ptr);
#endif