#include "error.h"
#include <stdlib.h>
#include <string.h>

const char* ERROR_NAMES[] = {
    "SyntaxError",
};

void free_error(Error error) {
    free(error.message);
}

Error create_error(ErrorType type, char* message, size_t size) {
    char* msg = malloc(sizeof(char) * size);
    strcpy(msg, message);

    Error error = { type, msg };
    return error;
}