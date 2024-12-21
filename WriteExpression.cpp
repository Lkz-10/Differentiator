#include "WriteExpression.h"

int WriteExpression(Node* root, Node* d_root, const char* file_name)
{
    if (!root || !file_name)
    {
        fprintf(stderr, "WriteExpression() error: root(%p), file name(%s)!\n", root, file_name);
        return ERROR;
    }

    FILE* file_ptr = fopen(file_name, "w");

    fprintf(file_ptr, "Expression: ");

    WriteNode(root, file_ptr);

    fprintf(file_ptr, "\n\nDifferentiated expression: ");

    WriteNode(d_root, file_ptr);

    fprintf(file_ptr, "\n");

    return OK;
}

int WriteNode(Node* node, FILE* file_ptr)
{
    if (!node) return OK;

    if (node->type == NUM)
    {
        fprintf(file_ptr, "%lg", node->value.num_value);
        return OK;
    }

    if (node->type == VAR)
    {
        fprintf(file_ptr, "x");
        return OK;
    }

    if (node->value.op_value == SIN || node->value.op_value == COS || node->value.op_value == LN)
    {
        fprintf(file_ptr, "%s(", OperatorName(node->value.op_value));

        WriteNode(node->left, file_ptr);

        fprintf(file_ptr, ")");

        return OK;
    }

    if (node->value.op_value == MUL || node->value.op_value == DIV)
    {
        if (node->left->type == OP && (node->left->value.op_value == ADD || node->left->value.op_value == SUB))
        {
            fprintf(file_ptr, "(");

            WriteNode(node->left, file_ptr);

            fprintf(file_ptr, ")");
        }

        else
        {
            WriteNode(node->left, file_ptr);
        }

        fprintf(file_ptr, " %s ", OperatorName(node->value.op_value));

        if (node->right->type == OP && (node->right->value.op_value == ADD || node->right->value.op_value == SUB))
        {
            fprintf(file_ptr, "(");

            WriteNode(node->right, file_ptr);

            fprintf(file_ptr, ")");
        }

        else
        {
            WriteNode(node->right, file_ptr);
        }

        return OK;
    }

    if (node->value.op_value == POW)
    {
        if (node->left->type == OP)
        {
            fprintf(file_ptr, "(");

            WriteNode(node->left, file_ptr);

            fprintf(file_ptr, ")");
        }

        else
        {
            WriteNode(node->left, file_ptr);
        }

        fprintf(file_ptr, "^");

        if (node->right->type == OP)
        {
            fprintf(file_ptr, "(");

            WriteNode(node->right, file_ptr);

            fprintf(file_ptr, ")");
        }

        else
        {
            WriteNode(node->right, file_ptr);
        }

        return OK;
    }

    WriteNode(node->left, file_ptr);

    fprintf(file_ptr, " %s ", OperatorName(node->value.op_value));

    WriteNode(node->right, file_ptr);

    return OK;
}

const char* OperatorName(int code)
{
    if (code < 1 || code > OP_CNT)
    {
        fprintf(stderr, "OperatorName() error: wrong code(%d)!\n", code);
        return NULL;
    }

    for (int i = 0; i < OP_CNT; ++i)
    {
        if (code == operations[i].code)
        {
            return operations[i].name;
        }
    }

    return NULL;
}

