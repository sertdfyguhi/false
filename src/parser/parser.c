#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../bool.h"
#include "../error.h"
#include "../lexer/token.h"
#include "nodes.h"

static Node* get_node_r_leaf(Node* node, TokenType end) {
    Node* n = node;

    // checks if right is operator and if so check for the end tt
    while (n->right.type == NVT_NODE && (n->right.value.n->type == NVT_OPERATOR || n->right.value.n->value.value.i != end)) {
        n = n->right.value.n;
    }

    return n;
}

// advances to the next token while checking for EOF
static int EOF_advance(Token** tokens, Token* start, size_t size, Error* err_ptr) {
    if ((*tokens - start) > size) {
        *err_ptr = create_error(SyntaxError, 23, "unexpected end of file");
        return -1;
    }

    (*tokens)++;
    return 0;
}

int parse(Token* tokens, size_t tsize, Node** nodes_ptr, size_t* nsize_ptr, Error* err_ptr) {
    Node* nodes = malloc(sizeof(Node));
    nodes[0] = EMPTY_NODE;
    size_t size = 1;

    Token* start = tokens;

    while ((tokens - start) < tsize) {
        switch (tokens->type) {
            case TT_BREAK: {
                if (nodes[size - 1].type != NT_EMPTY) {
                    nodes = realloc(nodes, sizeof(Node) * ++size);
                    nodes[size - 1] = EMPTY_NODE;
                }
                tokens++;
                break;
            }

            case TT_PLUS:
            case TT_MINUS: {
                const TokenType op_type = tokens->type;
                if (EOF_advance(&tokens, start, tsize, err_ptr) == -1)
                    return -1;

                NodeValue nv;
                if (conv_tval_to_nv(*tokens, &nv, err_ptr) == -1)
                    return -1;

                bool is_unary = nodes[size - 1].type == NT_EMPTY;

                if (is_unary) {
                    nodes[size - 1].left = EMPTY_NV;
                } else {
                    if (nodes[size - 1].type == NT_VALUE) {
                        nodes[size - 1].left = nodes[size - 1].value;
                    } else {
                        Node* v = malloc(sizeof(Node));
                        memcpy(v, &nodes[size - 1], sizeof(Node));

                        nodes[size - 1].left = create_node_nv(v);
                    }
                }

                nodes[size - 1].type = is_unary ? NT_UNARYOP : NT_BINOP;

                nodes[size - 1].value.type = NVT_OPERATOR;
                nodes[size - 1].value.value.i = op_type;
                nodes[size - 1].right = nv;

                tokens++;
                break;
            }

            case TT_MUL:
            case TT_DIV:
            case TT_POWER: {
                if (nodes[size - 1].type == NT_EMPTY) {
                    *err_ptr = create_errorf(SyntaxError, 24, "unexpected operator '%c'", SYMBOLS[(*tokens).type - SYM_START_POS]);
                    return -1;
                }

                const TokenType op_type = tokens->type;
                if (EOF_advance(&tokens, start, tsize, err_ptr) == -1)
                    return -1;

                NodeValue nv;
                if (conv_tval_to_nv(*tokens, &nv, err_ptr) == -1)
                    return -1;

                Node* leaf = get_node_r_leaf(&nodes[size - 1], op_type == TT_POWER ? -1 : TT_POWER);
                Node* node = malloc(sizeof(Node));
                node->type = NT_BINOP;
                node->left = leaf->right;
                node->value.type = NVT_OPERATOR;
                node->value.value.i = op_type;
                node->right = nv;

                leaf->right = create_node_nv(node);
                tokens++;
                break;
            }

            default: {
                if (nodes[size - 1].type != NT_EMPTY) {
                    *err_ptr = create_error(SyntaxError, 18, "unexpected number");
                    return -1;
                }

                NodeValue nv;
                if (conv_tval_to_nv(*tokens++, &nv, err_ptr) == -1)
                    return -1;

                Node node = { NT_VALUE, EMPTY_NV, nv, EMPTY_NV };
                nodes[size - 1] = node;
                break;
            }
        };
    }

    *nodes_ptr = nodes;
    *nsize_ptr = size;
    return 0;
}