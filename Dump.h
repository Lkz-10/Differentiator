#ifndef __DUMP_H__
#define __DUMP_H__

#include <stdio.h>
#include <stdlib.h>

#include "DiffGlobals.h"

int DrawTree(Node* root, const char* file_name);
int DrawNode(Node* node, FILE* file_ptr);

#endif
