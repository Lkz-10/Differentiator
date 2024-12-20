#include "LexicalAnalysis_diff.h"

int FillTokens(tokens_t* tokens, const Expression_t* buffer)
{
    if (!tokens || !buffer)
    {
        fprintf(stderr, "Error in FillTokens(): tokens(%p), buffer(%p)!\n", tokens, buffer);
        return -1;
    }

    char* curr_ptr = buffer->string;

    while (curr_ptr < buffer->string + buffer->size)
    {
        SkipRubbish(&curr_ptr, buffer->string + buffer->size);

        if (curr_ptr >= buffer->string + buffer->size) break;

        if (isdigit(*curr_ptr))
        {
            double num = strtod(curr_ptr, &curr_ptr);

            tokens->array[tokens->cnt].type            = NUM;
            tokens->array[tokens->cnt].value.num_value = num;

            (tokens->cnt)++;

            //printf("New num: %lg\n",  tokens->array[tokens->cnt].num_val);

            continue;
        }

        int word_code = IsKeyWord(&curr_ptr);

        if (word_code < 0) return ERROR;

        if (word_code > 0)
        {
            tokens->array[tokens->cnt].type = OP;
            tokens->array[tokens->cnt].value.op_value = word_code;

            (tokens->cnt)++;

//             printf("Word_code: %d\ntoks_code: %d\ntoks_cnt:  %d\n", word_code,
//                     tokens->array[tokens->cnt - 1].code, tokens->cnt);
//
//             printf("New op: %d\n", tokens->array[tokens->cnt - 1].code);

            continue;
        }

        if (*curr_ptr == 'x')
        {
            tokens->array[tokens->cnt].type = VAR;

            curr_ptr++;

            (tokens->cnt)++;

            //printf("New id: %s\n", tokens->array[tokens->cnt].id_val);

            continue;
        }

        fprintf(stderr, "FillTokens() error: unknown token(%s), curr_ptr = %p\nprev: %s", curr_ptr, curr_ptr, curr_ptr - 2);

        return ERROR;
    }

    return OK;
}

int IsKeyWord(char** word)
{
    if (!word)
    {
        fprintf(stderr, "Error in IsKeyWord(): word(%p)!\n", word);
        return ERROR;
    }

    int size = 0;

    if (!isalnum(**word))
    {
        (*word)++;
        size = 1;
    }

    else
    {
        while (isalnum(**word))
        {
            (*word)++;
            size++;
        }
    }

    for (int i = 0; i < OP_CNT; i++)
    {
        if (strncmp((*word) - size, operations[i].name, size) == 0)
        {
            //printf("Recognized operation: %d\nCurrent character: '%c'\n", operations[i].code, **word);
            return operations[i].code;
        }
    }

    (*word) -= size;

    return 0;
}

int SkipRubbish(char** curr_ptr, const char* end_ptr)
{
    if (!curr_ptr || !end_ptr)
    {
        fprintf(stderr, "SkipRubbish() error: curr_ptr(%p), end_ptr(%p)!\n", curr_ptr, end_ptr);
        return ERROR;
    }

    while (*curr_ptr < end_ptr && isspace(**curr_ptr)) (*curr_ptr)++;

    return OK;
}

int TokensCtor(tokens_t* tokens, int size)
{
    if (!tokens)
    {
        fprintf(stderr, "TokensCtor() error: null-pointer!\n");
        return ERROR;
    }

    tokens->cnt      = 0;
    tokens->curr_ptr = 0;
    tokens->size     = size;

    tokens->array = (Node*) calloc(size, sizeof(Node));

    if (!tokens->array)
    {
        fprintf(stderr, "TokensCtor() memory error!\n");
        return ERROR;
    }

    return OK;
}

int TokensDtor(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "TokensDtor() error: null-pointer!\n");
        return ERROR;
    }

    tokens->cnt      = 0;
    tokens->curr_ptr = 0;

    free(tokens->array);
    tokens->array = NULL;

    return OK;
}
