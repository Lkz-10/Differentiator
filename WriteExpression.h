#ifndef __WRITE_EXPRESSION_H__
#define __WRITE_EXPRESSION_H__

#include <stdio.h>
#include <stdlib.h>

#include "DiffGlobals.h"
#include "MakeTree.h"

int         WriteExpression (Node* root, Node* d_root, const char* file_name);
int         WriteNode       (Node* node, FILE* file_ptr);
const char* OperatorName    (int   code);

#endif
