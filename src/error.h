#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>

typedef enum {
    SyntaxError,
} ErrorType;

extern const char* ERROR_NAMES[];

typedef struct {
    ErrorType type;
    char* message;
} Error;

void free_error(Error error);
Error create_error(ErrorType type, char* message, size_t size);

#endif