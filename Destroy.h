#ifndef __DESTROY_H__
#define __DESTROY_H__

#include <stdlib.h>

#include "DiffGlobals.h"

int TreeDtor    (Node* node);
int ClearNode   (Node* node);
int ClearBuffer (Expression_t* buffer);

#endif
