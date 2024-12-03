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

int CountX (Node* node)
{
    if (node->type == VAR) return 1;

    if (node->type == NUM) return 0;

    return CountX(node->left) + CountX(node->right);
}

int ConstEval(Node* node)
{
    if (node->type == NUM || node->type == VAR) return 0;

    if (CountX(node->left) == 0)
    {
        union values value_left = {};
        value_left.num_value = Eval(node->left);

        TreeDtor(node->left);

        node->left = NewNode(NUM, value_left, NULL, NULL);
    }
    else
    {
        ConstEval(node->left);
    }

    if (CountX(node->right) == 0)
    {
        union values value_right = {};
        value_right.num_value = Eval(node->right);

        TreeDtor(node->right);

        node->right = NewNode(NUM, value_right, NULL, NULL);
    }
    else
    {
        ConstEval(node->right);
    }

    return 0;
}
