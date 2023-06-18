#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TT_INT, // long
    TT_FLOAT, // double
    TT_BOOL, // int
    TT_STRING, // char*
    TT_NULL,
    TT_IDENTIFIER,

    TT_SEMICOLON,
    TT_COMMA,
    TT_LPAREN,
    TT_RPAREN,
    TT_LBRACKET,
    TT_RBRACKET,

    TT_PLUS,
    TT_MINUS,
    TT_MUL,
    TT_DIV,
    TT_POWER,
} TokenType;

// symbols token type start position
#define SYM_START_POS 6

extern const char* TOKENTYPE_NAMES[];
extern const char SYMBOLS[];

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