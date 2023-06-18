#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../bool.h"
#include "../error.h"
#include "token.h"

static void append(Token** arr, size_t* size, Token val) {
    *arr = realloc(*arr, sizeof(Token) * ++(*size));
    (*arr)[*size - 1] = val;
}

int tokenize(char* code, Token** tokens_ptr, size_t* tsize_ptr, Error* err_ptr) {
    Token* tokens = malloc(sizeof(Token));
    size_t size = 0;

    while (*code != '\0') {
        if (*code == ' ' || *code == '\t' || *code == '\r' || *code == '\n') {
            code++;
        } else if (isdigit(*code)) {
            Token token;
            if (tokenize_number(&code, &token, err_ptr) == -1)
                return -1;

            append(&tokens, &size, token);
        } else {
            char* message = malloc(sizeof(char) * 22);
            sprintf(message, "foreign character '%c'", *code);

            Error err = { SyntaxError, message };
            *err_ptr = err;

            return -1;
        }
    }

    *tsize_ptr = size;
    *tokens_ptr = tokens;
    return 0;
}

int tokenize_number(char** code, Token* token_ptr, Error* err_ptr) {
    char* nstr = malloc(sizeof(char));
    nstr[0] = *(*code)++;
    size_t size = 1;

    bool is_float = false;

    while (isdigit(**code) || **code == '.') {
        if (**code == '.') {
            if (is_float) {
                *err_ptr = create_error(SyntaxError, "multiple decimal point in number", 33);
                return -1;
            }
            is_float = true;
        }

        nstr = realloc(nstr, sizeof(char) * ++size);
        nstr[size - 1] = *(*code)++;
    }

    TokenValue tvalue;
    if (is_float)
        tvalue.f = atof(nstr);
    else
        tvalue.i = atol(nstr);

    Token token = {
        is_float ? TT_FLOAT : TT_INT,
        tvalue
    };

    *token_ptr = token;
    return 0;
}