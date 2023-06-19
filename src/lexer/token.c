#include "token.h"

const char* TOKENTYPE_NAMES[] = {
    "INT",
    "FLOAT",
    "STRING",

    "IDENTIFIER",

    "TRUE",
    "FALSE",
    "NULL",

    "IF",
    "ELSE",
    "WHILE",
    "FOR",
    "VAR",
    "FUNC",
    "RETURN",

    "SEMICOLON",
    "COMMA",
    "MARK",
    "EQUAL",
    "LPAREN",
    "RPAREN",
    "LBRACKET",
    "RBRACKET",
    "LCURLY",
    "RCURLY",

    "PLUS",
    "MINUS",
    "MUL",
    "DIV",
    "POWER",
};

// keywords
const char* KEYWORDS[] = {
    "true",
    "false",
    "null",

    "if",
    "else",
    "while",
    "for",
    "var",
    "func",
    "return",
};

// operators and punctuators
const char SYMBOLS[] = {
    ';',
    ',',
    '!',
    '=',
    '(',
    ')',
    '[',
    ']',
    '{',
    '}',

    '+',
    '-',
    '*',
    '/',
    '^',
};
