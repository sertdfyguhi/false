#ifndef TOKEN_H
#define TOKEN_H

extern const char* TOKENTYPE_NAMES[];

// TODO: object.child()
// TODO: ==, !=..
typedef enum {
    TT_INT, // long
    TT_FLOAT, // double
    TT_STRING, // char*

    TT_IDENTIFIER,

    TT_TRUE, // boolean
    TT_FALSE, // boolean
    TT_NULL,

    TT_IF,
    TT_ELSE,
    TT_WHILE,
    TT_FOR,
    TT_VAR,
    TT_FUNC,
    TT_RETURN,

    TT_NOT, // exclamation mark
    TT_EQUAL,
    TT_COMMA,
    TT_LPAREN,
    TT_RPAREN,
    TT_LBRACKET,
    TT_RBRACKET,
    TT_LCURLY,
    TT_RCURLY,

    TT_PLUS,
    TT_MINUS,
    TT_MUL,
    TT_DIV,
    TT_POWER,
    TT_MOD,

    TT_SEMICOLON,
} TokenType;

// keyword token type start position
#define KW_START_POS 4
#define KW_END_POS 13

// symbols & operator token type start position
#define SYM_START_POS 14
#define SYM_END_POS 28

extern const char* KEYWORDS[];
extern const char SYMBOLS[];

typedef union {
    long i;
    double f;
    char* s;
} TokenValue;

typedef struct {
    TokenType type;
    TokenValue value;
} Token;

#endif