#include <stdio.h>

#include "lexer/token.h"
#include "parser/nodes.h"

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

    "BREAK",
};

const char* NODETYPE_NAMES[] = {
    "VALUE",

    "BINOP",
    "UNARYOP",
    "ASSIGN",

    "EMPTY",
};

const char* NODEVALUE_NAMES[] = {
    "INT",
    "FLOAT",
    "STRING",
    "TRUE",
    "FALSE",
    "NULL",

    "IDENTIFIER",

    "OPERATOR",
    "NODE",
    "EMPTY",
};

void print_token(Token token) {
    printf("%s(", TOKENTYPE_NAMES[token.type]);

    switch (token.type) {
        case TT_INT:
            printf("%ld", token.value.i);
            break;

        case TT_FLOAT:
            printf("%f", token.value.f);
            break;

        case TT_STRING:
        case TT_IDENTIFIER:
            printf("\"%s\"", token.value.s);
            break;

        default:
            printf("%s", TOKENTYPE_NAMES[token.type]);
            break;
    }

    printf(")");
}

void print_tokens(Token* tokens, size_t size) {
    for (int i = 0; i < size; i++) {
        print_token(tokens[i]);
        printf(", ");
    }
    printf("\n");
}

void print_node(Node node);

void print_nv(NodeValue nv) {
    printf("%s(", NODEVALUE_NAMES[nv.type]);

    switch (nv.type) {
        case NVT_INT:
            printf("%ld", nv.value.i);
            break;

        case NVT_FLOAT:
            printf("%f", nv.value.f);
            break;

        case NVT_STRING:
        case NVT_IDENTIFIER:
            printf("\"%s\"", nv.value.s);
            break;

        case NVT_OPERATOR:
            printf("%c", SYMBOLS[nv.value.i - SYM_START_POS]);
            break;

        case NVT_NODE:
            print_node(*nv.value.n);
            break;

        default:
            break;
    }

    printf(")");
}

void print_node(Node node) {
    printf("%s(", NODETYPE_NAMES[node.type]);
    print_nv(node.left);
    printf(", ");
    print_nv(node.value);
    printf(", ");
    print_nv(node.right);
    printf(")");
}

void print_nodes(Node* nodes, size_t size) {
    for (int i = 0; i < size; i++) {
        print_node(nodes[i]);
        printf("\n");
    }
}