#include "error.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* ERROR_NAMES[] = {
    "SyntaxError",
};

void free_error(Error error) {
    free(error.message);
}

Error create_error(ErrorType type, size_t msize, char* message) {
    char* msg = malloc(sizeof(char) * msize);
    strcpy(msg, message);

    const Error error = { type, msg };
    return error;
}

Error create_errorf(ErrorType type, size_t msize, char* fmessage, ...) {
    // get vargs for format string
    va_list args;
    va_start(args, fmessage);

    char* msg = malloc(sizeof(char) * msize);
    vsprintf(msg, fmessage, args);

    va_end(args);

    const Error error = { type, msg };
    return error;
}