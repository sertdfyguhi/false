#ifndef NODES_H
#define NODES_H

#include "../error.h"
#include "../lexer/token.h"

typedef enum {
    NVT_INT,
    NVT_FLOAT,
    NVT_STRING,
    NVT_TRUE,
    NVT_FALSE,
    NVT_NULL,

    NVT_IDENTIFIER,

    NVT_OPERATOR,
    NVT_NODE,
} NodeValueType;

typedef struct Node Node;

typedef struct {
    NodeValueType type;
    union {
        Node* n;
        long i;
        double f;
        char* s;
    } value;
} NodeValue;

typedef enum {
    NT_VALUE,

    NT_BINOP,
    NT_UNARYOP,
    NT_ASSIGN,
    NT_IF,
    NT_FOR,
    NT_WHILE,
} NodeType;

struct Node {
    NodeType type;

    NodeValue* left;
    NodeValue* value;
    NodeValue* right;
};

extern const char* NODETYPE_NAMES[];
extern const char* NODEVALUE_NAMES[];
NodeValue* create_nv_from_node(Node* node);
int create_nv_from_tval(Token token, NodeValue* nv_ptr, Error* err_ptr);

#endif