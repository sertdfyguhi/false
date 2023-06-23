#include "nodes.h"

#include "../bool.h"
#include "../error.h"
#include "../lexer/token.h"

const NodeValue EMPTY_NV = { NVT_EMPTY, { .i = 0 } };
const Node EMPTY_NODE = {
    NT_EMPTY,
    { NVT_EMPTY, { .i = 0 } },
    { NVT_EMPTY, { .i = 0 } },
    { NVT_EMPTY, { .i = 0 } },
};

NodeValue create_node_nv(Node* node) {
    // if (node->type == NT_VALUE)
    //     return node->value;

    NodeValue nv = { NVT_NODE, { .n = node } };
    return nv;
}

int conv_tval_to_nv(Token token, NodeValue* nv_ptr, Error* err_ptr) {
    switch (token.type) {
        case TT_INT:
            nv_ptr->type = NVT_INT;
            nv_ptr->value.i = token.value.i;
            break;

        case TT_FLOAT:
            nv_ptr->type = NVT_FLOAT;
            nv_ptr->value.f = token.value.f;
            break;

        case TT_STRING:
            nv_ptr->type = NVT_STRING;
            nv_ptr->value.s = token.value.s;
            break;

        case TT_IDENTIFIER:
            nv_ptr->type = NVT_IDENTIFIER;
            nv_ptr->value.s = nv_ptr->value.s;
            break;

        case TT_TRUE:
            nv_ptr->type = NVT_TRUE;
            nv_ptr->value.i = 1;
            break;

        case TT_FALSE:
            nv_ptr->type = NVT_FALSE;
            nv_ptr->value.i = 0;
            break;

        case TT_NULL:
            nv_ptr->type = NVT_NULL;
            nv_ptr->value.i = 0;
            break;

        default:
            *err_ptr = create_errorf(SyntaxError, 22, "unexpected symbol '%c'", SYMBOLS[token.type - SYM_START_POS]);
            break;
    }

    return 0;
}