#ifndef LEXER_H
#define LEXER_H

#include "../error.h"
#include "token.h"
#include <stdlib.h>

int tokenize(char* code, Token** tokens_ptr, size_t* tsize_ptr, Error* err_ptr);
int tokenize_number(char** code, Token* token_ptr, Error* err_ptr);
int tokenize_string(char** code, Token* token_ptr, Error* err_ptr);

#endif