#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TT_INT, // long
    TT_FLOAT, // double
    TT_BOOL, // int
    TT_STRING, // char*
    TT_NULL,
    TT_IDENTIFIER,

    TT_COMMA,
    TT_PLUS,
    TT_MINUS,
    TT_MUL,
    TT_DIV,
} TokenType;

extern const char* TOKENTYPE_NAMES[];

typedef union {
    long i;
    double f;
    char* s;
} TokenValue;

typedef struct {
    int type;
    TokenValue value;
} Token;

#endif