#include "lexer.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        Token token;

        if (*code == ' ' || *code == '\t' || *code == '\r' || *code == '\n') {
            code++;
            continue;
        } else if (*code == ';') {
            token.type = TT_SEMICOLON;
            token.value.i = 0;
            code++;
        } else if (*code == '#') {
            while (*code != '\n' && *code != '\0') {
                code++;
            }
            continue;
        } else if (*code == '\'' || *code == '"') {
            if (tokenize_string(&code, &token, err_ptr) == -1)
                return -1;
        } else if (isdigit(*code)) {
            if (tokenize_number(&code, &token, err_ptr) == -1)
                return -1;
        } else if (isalpha(*code) || *code == '_') {
            if (tokenize_identifier(&code, &token, err_ptr) == -1)
                return -1;
        } else {
            const char* sym = strchr(SYMBOLS, *code);

            if (sym) {
                // starting index for operators + index
                token.type = SYM_START_POS + (sym - SYMBOLS);
                token.value.i = 0;
                code++;
            } else {
                *err_ptr = create_errorf(SyntaxError, 22, "foreign character '%c'", *code);
                return -1;
            }
        }

        append(&tokens, &size, token);
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
                *err_ptr = create_error(SyntaxError, 33, "multiple decimal point in number");
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

const char ESCAPES[] = {
    't',
    'r',
    'n',
    '"',
    '\'',
    '\\'
};

const char ESCAPES_CHAR[] = {
    '\t',
    '\r',
    '\n',
    '"',
    '\'',
    '\\'
};

int tokenize_string(char** code, Token* token_ptr, Error* err_ptr) {
    const char quote = **code;

    char* str = malloc(sizeof(char));
    str[0] = *++(*code) == quote ? '\0' : **code;
    size_t size = 1;

    bool is_escape = false;

    (*code)++;
    while (is_escape || **code != quote) {
        if (**code == '\0') {
            *err_ptr = create_error(SyntaxError, 23, "unexpected end of file");
            return -1;
        } else if (**code == '\n') {
            *err_ptr = create_error(SyntaxError, 23, "unexpected end of line");
            return -1;
        } else if (!is_escape && **code == '\\') {
            is_escape = true;
            (*code)++;
            continue;
        }

        str = realloc(str, sizeof(char) * ++size);

        if (is_escape) {
            is_escape = false;
            const char* escape = strchr(ESCAPES, *(*code)++);

            if (escape) {
                // subtracting the found pointer from the first pointer gets index
                str[size - 1] = ESCAPES_CHAR[escape - ESCAPES];
            } else {
                *err_ptr = create_errorf(SyntaxError, 20, "invalid escape '\\%c'", **code);
                return -1;
            }
        } else {
            str[size - 1] = *(*code)++;
        }
    }

    (*code)++;

    Token token = {
        TT_STRING,
        { .s = str }
    };
    *token_ptr = token;
    return 0;
}

int tokenize_identifier(char** code, Token* token_ptr, Error* err_ptr) {
    char* iden = malloc(sizeof(char));
    iden[0] = *(*code)++;
    size_t size = 1;

    while (isalnum(**code) || **code == '_') {
        iden = realloc(iden, sizeof(char) * ++size);
        iden[size - 1] = *(*code)++;
    }

    bool is_keyword = false;
    int i;

    for (i = 0; i < KW_END_POS - KW_START_POS + 1; i++) {
        // check if string are equal
        if (strcmp(KEYWORDS[i], iden) == 0) {
            is_keyword = true;
            break;
        }
    }

    Token token = {
        is_keyword ? KW_START_POS + i : TT_IDENTIFIER,
        { .s = iden }
    };
    *token_ptr = token;
    return 0;
}
