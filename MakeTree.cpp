#include "MakeTree.h"

void SyntaxError(Expression_t* buffer)
{
    fprintf(stderr, "Syntax error, s[p] = '%c'\n", buffer->string[buffer->curr_ptr]);

    exit(0);
}

#define _VAR(val)           NewNode(VAR, (val), NULL, NULL)
#define _NUM(val)           NewNode(NUM, (val), NULL, NULL)
#define _OP(op, val1, val2) NewNode(OP, (op), (val1), (val2))

Node* GetN(Expression_t* buffer)
{
    int old_ptr = buffer->curr_ptr;

    double val = 0;

    while ('0' <= buffer->string[buffer->curr_ptr] && buffer->string[buffer->curr_ptr] <= '9')
    {
        val = val*10 + buffer->string[buffer->curr_ptr] - '0';
        (buffer->curr_ptr)++;
    }

    if (buffer->curr_ptr == old_ptr)
    {
        SyntaxError(buffer);
    }

    union values val_ret = {};
    val_ret.num_value = val;

    return _NUM(val_ret);
}

Node* GetV(Expression_t* buffer)
{
    union values value = {};

    value.var_value = buffer->string[buffer->curr_ptr];

    (buffer->curr_ptr)++;

    return _VAR(value);
}

Node* GetP(Expression_t* buffer)
{
    if (buffer->string[buffer->curr_ptr] == '(')
    {
        (buffer->curr_ptr)++;

        Node* val = GetE(buffer);

        if (buffer->string[buffer->curr_ptr] != ')')
        {
            SyntaxError(buffer);
        }

        (buffer->curr_ptr)++;

        return val;
    }

    if (buffer->string[buffer->curr_ptr] == 'x') return GetV(buffer);

    return GetN(buffer);
}

Node* GetT(Expression_t* buffer)
{
    Node* val = GetP(buffer);

    while (buffer->string[buffer->curr_ptr] == '*' || buffer->string[buffer->curr_ptr] == '/')
    {
        int op = buffer->string[buffer->curr_ptr];

        (buffer->curr_ptr)++;

        Node* val2 = GetP(buffer);

        union values op_code = {};

        if (op == '*')
        {
            op_code.op_value = MUL;

            val = _OP(op_code, val, val2);
        }
        else
        {
            op_code.op_value = DIV;

            val = _OP(op_code, val, val2);
        }
    }

    return val;
}

Node* GetE(Expression_t* buffer)
{
    Node* val = GetT(buffer);

    while (buffer->string[buffer->curr_ptr] == '+' || buffer->string[buffer->curr_ptr] == '-')
    {
        int op = buffer->string[buffer->curr_ptr];

        (buffer->curr_ptr)++;

        Node* val2 = GetT(buffer);

        union values op_code = {};

        if (op == '+')
        {
            op_code.op_value = ADD;

            val = _OP(op_code, val, val2);
        }
        else
        {
            op_code.op_value = SUB;

            val = _OP(op_code, val, val2);
        }
    }

    return val;
}

Node* GetG(Expression_t* buffer)
{
    Node* val = GetE(buffer);

    if (buffer->string[buffer->curr_ptr] != '$') SyntaxError(buffer);

    (buffer->curr_ptr)++;

    return val;
}

Node* NewNode(int type, union values value, Node* left, Node* right)
{
    Node* node = (Node*) calloc(1, sizeof(Node));

    if (!node)
    {
        fprintf(stderr, "Memory error!\n");
        return NULL;
    }

    node->type  = type;

    switch(type)
    {
        case NUM:
        {
            node->value = value;
            break;
        }
        case VAR:
        {
            node->value = value;
            break;
        }
        case OP:
        {
            node->value = value;
            break;
        }
        default:
        {
            fprintf(stderr, "Unknown type: %d!\n", type);
            return NULL;
        }
    }

    node->right = right;
    node->left  = left;

    return node;
}

// Node* GetTree(char* buf_ptr)
// {
//     if (!buf_ptr)
//     {
//         fprintf(stderr, "Buffer reading error!\n");
//         return NULL;
//     }
//
//     buf_ptr++;
//
//     if (isdigit(*buf_ptr))
//     {
//         //char value_string[MAX_LINE_LENGTH] = {};
//         //int  ptr_shift;
//         //
//         //sscanf(buf_ptr, "%[^)])%n", value_string, &ptr_shift);
//         //
//         //buf_ptr += ptr_shift;
//
//         Node* node = _NUM(strtod(buf_ptr, &buf_ptr));
//
//         buf_ptr++;
//
//         return node;
//     }
//
//     if (*buf_ptr == 'x')
//     {
//         buf_ptr += 2;
//
//         return _X;
//     }
//
//     char op_name[MAX_LINE_LENGTH] = {};
//
//     int  ptr_shift = 0;
//
//     sscanf(buf_ptr, "%[^(]%n", op_name, &ptr_shift);
//
//     buf_ptr += ptr_shift;
//
//     for (int i = 0; i < OP_CNT; ++i)
//     {
//         if (stricmp(op_name, (operations[i]).name) == 0)
//         {
//             return NewNode(OP, (operations[i]).code, GetTree(buf_ptr), GetTree(buf_ptr));
//         }
//     }
//
//     fprintf(stderr, "Error: wrong operation: %s!\n", op_name);
//
//     return NULL;
// }

#undef _NUM
#undef _OP
#undef _X
