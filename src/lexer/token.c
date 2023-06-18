#include "token.h"

const char* TOKENTYPE_NAMES[] = {
    "INT",
    "FLOAT",
    "BOOL",
    "STRING",
    "NULL",
    "IDENTIFIER",

    "SEMICOLON",
    "COMMA",
    "LPAREN",
    "RPAREN",
    "LBRACKET",
    "RBRACKET",

    "PLUS",
    "MINUS",
    "MUL",
    "DIV",
    "POWER",
};

// operators and punctuators
const char SYMBOLS[] = {
    ';',
    ',',
    '(',
    ')',
    '[',
    ']',

    '+',
    '-',
    '*',
    '/',
    '^',
};