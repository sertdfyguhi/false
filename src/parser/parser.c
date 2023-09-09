#include "parser.h"

#include "../error.h"
#include "../lexer/token.h"
#include "nodes.h"

#include <stdio.h>
#include <stdlib.h>

#define next                                       \
    if (next_EOS(tokens, i, tsize, err_ptr) == -1) \
        return -1;

static void append(Node** arr, size_t* size, Node val) {
    *arr = realloc(*arr, sizeof(Node) * ++(*size));
    (*arr)[*size - 1] = val;
}

static int next_EOS(Token* tokens, size_t* i, size_t tsize, Error* err_ptr) {
    if (++(*i) >= tsize || tokens[*i].type == TT_SEMICOLON) {
        *err_ptr = create_error(SyntaxError, 28, "unexpected end of statement");
        return -1;
    } else {
        return 0;
    }
}

int parse(Token* tokens, size_t tsize, Node** statements_ptr, size_t* stmtsize_ptr, Error* err_ptr) {
    Node* statements = malloc(sizeof(Node));
    size_t size = 1;

    // at max value so it rollsback on first iteration
    size_t i = SIZE_MAX;

    Node ast;

    while (++i < tsize) {
        switch (tokens[i].type) {
            case TT_VAR:
                if (parse_assign(tokens, &i, tsize, &ast, err_ptr) == -1)
                    return -1;
                break;

            case TT_IF:
                if (parse_block(NT_IF, tokens, &i, tsize, &ast, err_ptr) == -1)
                    return -1;
                break;

            case TT_FOR:;
                if (parse_block(NT_FOR, tokens, &i, tsize, &ast, err_ptr) == -1)
                    return -1;
                break;

            case TT_WHILE:
                if (parse_block(NT_WHILE, tokens, &i, tsize, &ast, err_ptr) == -1)
                    return -1;
                break;

            case TT_IDENTIFIER:
                /* code */
                break;

            // math op
            case TT_INT:
            case TT_FLOAT:
            case TT_MINUS: // unary
            case TT_PLUS:
                /* code */
                break;

            default:
                break;
        }

        append(&statements, &size, ast);
    }

    *statements_ptr = statements;
    *stmtsize_ptr = size;
    return 0;
}

int parse_assign(Token* tokens, size_t* i, size_t tsize, Node* ast_ptr, Error* err_ptr) {
    next;

    if (tokens[*i].type == TT_IDENTIFIER) {
        NodeValue* name_nv = malloc(sizeof(NodeValue));
        name_nv->type = NVT_STRING;
        name_nv->value.s = tokens[*i].value.s;
        next;

        if (tokens[*i].type == TT_EQUAL) {
            next;

            Node* value = malloc(sizeof(Node));
            if (parse_expr(tokens, i, tsize, value, err_ptr) == -1)
                return -1;

            ast_ptr->type = NT_ASSIGN;
            ast_ptr->left = name_nv;
            ast_ptr->value = create_nv_from_node(value);
            return 0;
        } else {
            *err_ptr = create_errorf(
                SyntaxError,
                29,
                "expected =, found %s",
                TOKENTYPE_NAMES[tokens[*i].type]);

            return -1;
        }
    } else {
        *err_ptr = create_errorf(SyntaxError, 22, "unexpected %s", TOKENTYPE_NAMES[tokens[*i].type]);
        return -1;
    }

    return 0;
}

int parse_block(NodeType type, Token* tokens, size_t* i, size_t tsize, Node* ast_ptr, Error* err_ptr) {
    return 0;
}

int parse_value(Token* tokens, size_t* i, size_t tsize, NodeValue* nv_ptr, Error* err_ptr) {
    return 0;
}

int parse_expr(Token* tokens, size_t* i, size_t tsize, Node* ast_ptr, Error* err_ptr) {
    while (next_EOS(tokens, i, tsize, NULL) != -1) {
    }

    return 0;
}