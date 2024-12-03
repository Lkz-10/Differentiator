#ifndef __SIMPLIFIER_H__
#define __SIMPLIFIER_H__

#include <stdio.h>
#include <stdlib.h>

#include "DiffGlobals.h"
#include "MakeTree.h"
#include "Destroy.h"

data_t Eval      (Node* node);

int    CountX    (Node* node);
int    ConstEval (Node* node);

#endif
