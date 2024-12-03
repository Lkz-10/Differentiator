#include "Differentiator.h"

#define _NUM(val)                   NewNode(NUM, (val), NULL, NULL)
#define _OP(op_code, val1, val2)   NewNode(OP, op_code, (val1), (val2))
// #define _SUB(val1, val2)    NewNode(OP, SUB, (val1), (val2))
// #define _MUL(val1, val2)    NewNode(OP, MUL, (val1), (val2))
// #define _DIV(val1, val2)    NewNode(OP, DIV, (val1), (val2))

Node* Diff(Node* node)
{
    union values value = {};

    if (node->type == NUM)
    {
        value.num_value = 0;
        return _NUM(value);
    }

    if (node->type == VAR)
    {
        value.num_value = 1;
        return _NUM(value);
    }

    switch (node->value.op_value)
    {
        case ADD:
        {
            value.op_value = ADD;

            return _OP(value, Diff(node->left), Diff(node->right));
        }

        case SUB:
        {
            value.op_value = SUB;

            return _OP(value, Diff(node->left), Diff(node->right));
        }

        case MUL:
        {
            Node* dL = Diff(node->left);
            Node* dR = Diff(node->right);

            Node* cL = Copy(node->left);
            Node* cR = Copy(node->right);

            value.op_value = MUL;

            union values value_add = {};
            value_add.op_value     = ADD;

            return _OP(value_add, _OP(value, dL, cR), _OP(value, cL, dR));
        }

        case DIV:
        {
            Node* dL = Diff(node->left);
            Node* dR = Diff(node->right);

            Node* cL = Copy(node->left);
            Node* cR = Copy(node->right);

            value.op_value = MUL;

            union values value_sub = {};
            union values value_div = {};

            value_sub.op_value = SUB;
            value_div.op_value = DIV;

            return _OP(value_div, _OP(value_sub, _OP(value, dL, cR), _OP(value, cL, dR)), _OP(value, cR, cR));
        }

        default:
        {
            fprintf(stderr, "Differentiator error: unknown operation code: %d!\n", node->value.op_value);

            return NULL;
        }
    }
}

Node* Copy(Node* node)
{
    if (!node)
    {
        return NULL;
    }

    Node* copied_node = NewNode(node->type, node->value, Copy(node->left), Copy(node->right));

    return copied_node;
}
