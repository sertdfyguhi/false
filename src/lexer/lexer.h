#ifndef LEXER_H
#define LEXER_H

#include "../error.h"
#include "token.h"
#include <stdlib.h>

extern const char SYMBOLS[];
extern const TokenType SYMBOLS_TT[];

extern const char ESCAPES[];
extern const char ESCAPES_CHAR[];

int tokenize(char* code, Token** tokens_ptr, size_t* tsize_ptr, Error* err_ptr);
int tokenize_number(char** code, Token* token_ptr, Error* err_ptr);
int tokenize_string(char** code, Token* token_ptr, Error* err_ptr);

#endif