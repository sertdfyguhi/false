#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "lexer/lexer.h"
#include "lexer/token.h"

void print_token(Token token) {
    printf("%s(", TOKENTYPE_NAMES[token.type]);

    switch (token.type) {
        case TT_INT:
            printf("%ld", token.value.i);
            break;

        case TT_FLOAT:
            printf("%f", token.value.f);
            break;

        case TT_BOOL:
            printf("%s", token.value.i ? "true" : "false");
            break;

        case TT_STRING:
        case TT_IDENTIFIER:
            printf("\"%s\"", token.value.s);
            break;

        case TT_NULL:
        case TT_COMMA:
        case TT_PLUS:
        case TT_MINUS:
        case TT_MUL:
        case TT_DIV:
            printf("%s", TOKENTYPE_NAMES[token.type]);
            break;

        default:
            break;
    }

    printf(")");
}

void print_tokens(Token* tokens, size_t size) {
    for (int i = 0; i < size; i++) {
        print_token(tokens[i]);
        printf(", ");
    }
    printf("\n");
}

int run(char* code) {
    Token* tokens;
    size_t tsize;
    Error error;

    if (tokenize(code, &tokens, &tsize, &error) == -1) {
        printf("%s: %s\n", ERROR_NAMES[error.type], error.message);
        free_error(error);
        return -1;
    }

    print_tokens(tokens, tsize);

    free(tokens);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("error: no file provided\n");
        return 1;
    }

    FILE* fptr = fopen(argv[1], "r");
    char* contents = malloc(sizeof(char));
    size_t size = 1;

    char c = fgetc(fptr);
    contents[0] = c;

    while (c != '\0') {
        c = fgetc(fptr);
        if (c == EOF)
            c = '\0';

        contents = realloc(contents, sizeof(char) * ++size);
        contents[size - 1] = c;
    }

    int s = run(contents);
    free(contents);
    return s == -1;
}