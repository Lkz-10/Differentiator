#include "Simplifier.h"

data_t Eval(Node* node)
{
    if (!node)
    {
        fprintf(stderr, "Evaluation error: node = NULL!\n");

        return POISON;
    }

    if (node->type == NUM)
    {
        return node->value.num_value;
    }

    if (node->type != OP)
    {
        fprintf(stderr, "Evaluation error: variable node!\n");

        return POISON;
    }

    data_t val1 = Eval(node->left);
    data_t val2 = Eval(node->right);

    if (val1 == POISON || val2 == POISON)
    {
        return POISON;
    }

    switch (node->value.op_value)
    {
        case ADD:
        {
            return val1 + val2;
        }

        case SUB:
        {
            return val1 - val2;
        }

        case MUL:
        {
            return val1 * val2;
        }

        case DIV:
        {
            return val1 / val2;
        }

        default:
        {
            fprintf(stderr, "Error: unknown operation code: %d!\n", node->value.op_value);

            return POISON;
        }
    }
}
