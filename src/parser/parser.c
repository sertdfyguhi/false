#include "parser.h"

#include "../error.h"
#include "../lexer/token.h"
#include "nodes.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define next_e                                     \
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
    }

    return 0;
}

static int next(Token* tokens, size_t* i, size_t tsize) {
    return ++(*i) >= tsize || tokens[*i].type == TT_SEMICOLON ? -1 : 0;
}

int parse(Token* tokens, size_t tsize, Node** statements_ptr, size_t* stmtsize_ptr, Error* err_ptr) {
    Node* statements = malloc(sizeof(Node));
    size_t size = 1;
    size_t i = 0;

    // make sure it doesnt increment on first index
    while ((i == 0 ? i : ++i) < tsize) {
        Node ast;

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
                if (parse_expr(tokens, &i, tsize, &ast, err_ptr) == -1)
                    return -1;
                break;

            default:
                break;
        }

        append(&statements, &size, ast);

        // increment after parsing first index
        if (i == 0)
            i++;
    }

    *statements_ptr = statements;
    *stmtsize_ptr = size;
    return 0;
}

int parse_assign(Token* tokens, size_t* i, size_t tsize, Node* ast_ptr, Error* err_ptr) {
    next_e;

    if (tokens[*i].type == TT_IDENTIFIER) {
        NodeValue* name_nv = malloc(sizeof(NodeValue));
        name_nv->type = NVT_STRING;
        name_nv->value.s = tokens[*i].value.s;
        next_e;

        if (tokens[*i].type == TT_EQUAL) {
            next_e;

            Node* value;
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

// TODO: handle brackets
int parse_value(Token* tokens, size_t* i, size_t tsize, NodeValue* nv_ptr, Error* err_ptr) {
    // check for unary
    if (tokens[*i].type == TT_MINUS) {
        next_e;

        TokenType tok_type = tokens[*i].type;

        if (tok_type != TT_INT && tok_type != TT_FLOAT && tok_type != TT_IDENTIFIER) {
            *err_ptr = create_error(SyntaxError, 22, "unexpected minus sign");
            return -1;
        }

        NodeValue* value = malloc(sizeof(NodeValue));
        if (create_nv_from_tval(tokens[*i], value, err_ptr) == -1)
            return -1;

        Node* unary_node = malloc(sizeof(Node));
        unary_node->type = NT_UNARY;
        unary_node->value = value;

        nv_ptr->type = NVT_NODE;
        nv_ptr->value.n = unary_node;
    } else {
        if (create_nv_from_tval(tokens[*i], nv_ptr, err_ptr) == -1)
            return -1;
    }

    return 0;
}

// TODO: handle brackets
int parse_expr(Token* tokens, size_t* i, size_t tsize, Node* ast_ptr, Error* err_ptr) {
    Node* ast = malloc(sizeof(Node));
    if (parse_value(tokens, i, tsize, ast, err_ptr) == -1)
        return -1;

    while (next(tokens, i, tsize) != -1) {
        switch (tokens[*i].type) {
            case TT_PLUS:
            case TT_MINUS:
                next_e;

                NodeValue* right = malloc(sizeof(Node));
                if (parse_value(tokens, i, tsize, right, err_ptr) == -1)
                    return -1;

                ast->type = NT_ADD;
                ast->left = ast;
                ast->right = right;
                break;

            case TT_MUL:
            case TT_DIV:
                break;

            case TT_MOD:
            case TT_POWER:
                break;
        }
    }

    return 0;
}