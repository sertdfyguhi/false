#ifndef PRINT_H
#define PRINT_H

#include <stdlib.h>

extern const char* TOKENTYPE_NAMES[];

extern const char* NODETYPE_NAMES[];
extern const char* NODEVALUE_NAMES[];

void print_token(Token token);
void print_tokens(Token* tokens, size_t size);

void print_nv(NodeValue nv);
void print_node(Node node);
void print_nodes(Node* nodes, size_t nsize);

#endif