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
    data_t val2 = 0;

    if (node->right) val2 = Eval(node->right);

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

        case SIN:
        {
            return sin(val1);
        }

        case COS:
        {
            return cos(val1);
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
    if (!node) return 0;

    if (node->type == VAR) return 1;

    if (node->type == NUM) return 0;

    return CountX(node->left) + CountX(node->right);
}

int ConstEval(Node* node)
{
    if (!node || node->type == NUM || node->type == VAR) return 0;

    int changes = 0;

    if (node->left->type == OP && CountX(node->left) == 0)
    {
        union values value_left = {};
        value_left.num_value = Eval(node->left);

        TreeDtor(node->left);

        node->left = NewNode(NUM, value_left, NULL, NULL);

        changes++;
    }
    else
    {
        ConstEval(node->left);
    }

    if (node->right && node->right->type == OP && CountX(node->right) == 0)
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

    return changes;
}

int CleanNeutral(Node* node)
{
    if (!node || node->type == NUM || node->type == VAR) return 0;

    int changes = 0;

    switch (node->value.op_value)
    {
        case ADD:
        {
            if (node->left->type == NUM && node->left->value.num_value == 0)
            {
                Node* subtree   = node->right;
                Node* zero_node = node->left;

                DuplicateNode(node, subtree);

                ClearNode(subtree);
                ClearNode(zero_node);

                changes++;
            }
            else if (node->right->type == NUM && node->right->value.num_value == 0)
            {
                Node* subtree = node->left;
                Node* zero_node = node->right;

                DuplicateNode(node, subtree);

                ClearNode(subtree);
                ClearNode(zero_node);

                changes++;
            }

            break;
        }

        case SUB:
        {
            if (node->right->type == NUM && node->right->value.num_value == 0)
            {
                Node* subtree = node->left;
                Node* zero_node = node->right;

                DuplicateNode(node, subtree);

                ClearNode(subtree);
                ClearNode(zero_node);

                changes++;
            }

            break;
        }

        case MUL:
        {
            if ((node->left->type  == NUM && node->left->value.num_value == 0) ||
                (node->right->type == NUM && node->right->value.num_value == 0))
            {
                TreeDtor(node->left);
                TreeDtor(node->right);

                node->type = NUM;

                node->value.num_value = 0;

                node->left  = NULL;
                node->right = NULL;

                changes++;

                break;
            }

            if (node->left->type == NUM && node->left->value.num_value == 1)
            {
                ClearNode(node->left);

                Node* subtree = node->right;

                DuplicateNode(node, subtree);

                ClearNode(subtree);

                changes++;
            }

            else if (node->right->type  == NUM && node->right->value.num_value == 1)
            {
                ClearNode(node->right);

                Node* subtree = node->left;

                DuplicateNode(node, subtree);

                ClearNode(subtree);

                changes++;
            }

            break;
        }

        case DIV:
        {
            if (node->right->type == NUM && node->right->value.num_value == 0)
            {
                fprintf(stderr, "Math error: division by zero!\n");
                return -1;
            }

            if (node->left->type  == NUM && node->left->value.num_value  == 0)
            {
                TreeDtor(node->left);
                TreeDtor(node->right);

                node->type = NUM;

                node->value.num_value = 0;

                node->left  = NULL;
                node->right = NULL;

                changes++;
            }

            break;
        }

        default:
            break;
    }

    return changes + CleanNeutral(node->left) + CleanNeutral(node->right);
}

int DuplicateNode(Node* dest, Node* source)
{
    if (!dest || !source)
    {
        fprintf(stderr, "Duplication error: dest(%p), source(%p)\n", dest, source);
        return -1;
    }

    dest->type = source->type;

    switch (source->type)
    {
        case NUM:
        {
            dest->value.num_value = source->value.num_value;
            break;
        }

        case VAR:
        {
            dest->value.var_value = source->value.var_value;
            break;
        }

        case OP:
        {
            dest->value.op_value = source->value.op_value;
            break;
        }

        default:
        {
            fprintf(stderr, "Unknown type for duplication: %d!\n", source->type);
            return -1;
        }
    }

    dest->left  = source->left;
    dest->right = source->right;

    return 0;
}

int Simplify(Node* root)
{
    int a = 0, b = 1;

    while (a + b > 0)
    {
        a = ConstEval(root);
        b = CleanNeutral(root);
    }

    return OK;
}
