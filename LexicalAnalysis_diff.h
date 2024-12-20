#ifndef __LEXICAL_ANALYSIS_H__
#define __LEXICAL_ANALYSIS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "DiffGlobals.h"

int FillTokens    (tokens_t* tokens, const Expression_t* buffer);
int IsKeyWord     (char** word);
int SkipRubbish   (char** curr_ptr, const char* end_ptr);
int TokensCtor    (tokens_t* tokens, int size);
int TokensDtor    (tokens_t* tokens);

#endif
