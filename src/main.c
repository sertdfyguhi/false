#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/parser.h"
#include "print.h"

int handle_error(Error error) {
    printf("%s: %s\n", ERROR_NAMES[error.type], error.message);
    free_error(error);
    return -1;
}

int run(char* code) {
    Error error;

    Token* tokens;
    size_t tsize;

    if (tokenize(code, &tokens, &tsize, &error) == -1)
        return handle_error(error);

    print_tokens(tokens, tsize);

    Node* nodes;
    size_t nsize;

    if (parse(tokens, tsize, &nodes, &nsize, &error) == -1)
        return handle_error(error);

    printf("%lu\n", nsize);
    print_nodes(nodes, nsize);

    // free tokens
    // for (int i = 0; i < tsize; i++) {
    //     if (tokens[i].type == TT_STRING) {
    //         free(tokens[i].value.s);
    //     }
    // }
    // free(tokens);

    // free nodes
    // for (int i = 0; i < nsize; i++) {

    // }
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

    int status = run(contents);
    return status == -1;
}