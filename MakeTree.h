#ifndef __MAKE_TREE_H__
#define __MAKE_TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "DiffGlobals.h"

Node* NewNode(int type, union values value, Node* left, Node* right);
//Node* GetTree(char* buf_ptr);

Node* GetG(tokens_t* tokens);
Node* GetE(tokens_t* tokens);
Node* GetT(tokens_t* tokens);
Node* GetP(tokens_t* tokens);
Node* GetN(tokens_t* tokens);
Node* GetV(tokens_t* tokens);

int OperatorCode(const char* _operator);

void SyntaxError(tokens_t* tokens, const char* expected_symbol);


#endif
