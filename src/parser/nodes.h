#ifndef NODE_H
#define NODE_H

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
    NVT_EMPTY,
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

    NT_EMPTY,
} NodeType;

struct Node {
    NodeType type;

    NodeValue left;
    NodeValue value;
    NodeValue right;
};

extern const char* NODETYPE_NAMES[];
extern const NodeValue EMPTY_NV;
extern const Node EMPTY_NODE;

NodeValue create_node_nv(Node* node);
int conv_tval_to_nv(Token token, NodeValue* nv_ptr, Error* err_ptr);

#endif