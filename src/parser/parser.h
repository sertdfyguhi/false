#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>

#include "../error.h"
#include "../lexer/token.h"
#include "nodes.h"

int parse(Token* tokens, size_t tsize, Node** nodes_ptr, size_t* nsize_ptr, Error* err_ptr);

#endif