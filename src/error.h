#ifndef ERROR_H
#define ERROR_H

#include <stddef.h>

typedef enum {
    SyntaxError,
} ErrorType;

extern const char* ERROR_NAMES[];

typedef struct {
    ErrorType type;
    char* message;
} Error;

void free_error(Error error);
Error create_error(ErrorType type, size_t msize, char* message);
Error create_errorf(ErrorType type, size_t msize, char* message, ...);

#endif