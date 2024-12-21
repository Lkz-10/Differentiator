#include "Differentiator.h"

#define _NUM(val)                  NewNode(NUM, (val), NULL, NULL)
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
            //value.op_value = ADD;

            return _OP({.op_value = ADD}, Diff(node->left), Diff(node->right));
        }

        case SUB:
        {
            //value.op_value = SUB;

            return _OP({.op_value = SUB}, Diff(node->left), Diff(node->right));
        }

        case MUL:
        {
            Node* dL = Diff(node->left);
            Node* dR = Diff(node->right);

            Node* cL = Copy(node->left);
            Node* cR = Copy(node->right);

//             value.op_value = MUL;
//
//             union values value_add = {};
//             value_add.op_value     = ADD;

            return _OP({.op_value = ADD}, _OP({.op_value = MUL}, dL, cR), _OP({.op_value = MUL}, cL, dR));
        }

        case DIV:
        {
            Node* dL = Diff(node->left);
            Node* dR = Diff(node->right);

            Node* cL = Copy(node->left);
            Node* cR = Copy(node->right);

            Node* cR_den1 = Copy(node->right);
            Node* cR_den2 = Copy(node->right);

            return _OP({.op_value = DIV}, _OP({.op_value = SUB}, _OP({.op_value = MUL}, dL, cR),
                   _OP({.op_value = MUL}, cL, dR)), _OP({.op_value = MUL}, cR_den1, cR_den2));
        }

        case SIN:
        {
            Node* dx = Diff(node->left);

            return _OP({.op_value = MUL}, _OP({.op_value = COS}, Copy(node->left), NULL), dx);
        }

        case COS:
        {
            Node* dx = Diff(node->left);

            union values zero_value = {};
            zero_value.num_value = 0;

            return _OP({.op_value = MUL}, _OP({.op_value = SUB}, _NUM(zero_value), _OP({.op_value = SIN},
                       Copy(node->left), NULL)), dx);
        }

        case POW:
        {
            if (CountX(node->left) == 0 && CountX(node->right) == 0)
            {
                value.num_value = 0;

                return _NUM(value);
            }

            if (CountX(node->right) == 0)
            {
                value.num_value = 1;

                return _OP({.op_value = MUL}, _OP({.op_value = MUL}, Copy(node->right),
                       _OP({.op_value = POW}, Copy(node->left),
                       _OP({.op_value = SUB}, Copy(node->right), _NUM(value)))), Diff(node->left));
            }

            if (CountX(node->left) == 0)
            {
                return _OP({.op_value = MUL}, Copy(node), _OP({.op_value = MUL},
                       _OP({.op_value = LN}, Copy(node->left), NULL), Diff(node->right)));
            }

            return _OP({.op_value = MUL}, Copy(node), Diff(_OP({.op_value = MUL}, Copy(node->right),
                   _OP({.op_value = LN},  Copy(node->left), NULL))));
        }

        case LN:
        {
            return _OP({.op_value = DIV}, Diff(node->left), Copy(node->left));
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
