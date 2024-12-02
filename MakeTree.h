#ifndef __MAKE_TREE_H__
#define __MAKE_TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "DiffGlobals.h"

Node* NewNode(int type, union values value, Node* left, Node* right);
//Node* GetTree(char* buf_ptr);

Node* GetG(Expression_t* buffer);
Node* GetE(Expression_t* buffer);
Node* GetT(Expression_t* buffer);
Node* GetP(Expression_t* buffer);
Node* GetN(Expression_t* buffer);

void SyntaxError(Expression_t* buffer);

#endif
