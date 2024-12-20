#include "MakeTree.h"

void SyntaxError(tokens_t* tokens, const char* expected_symbol)
{
    fprintf(stderr, "Syntax error, current token: %d (expected '%s')\n",
            tokens->curr_ptr, expected_symbol);

    exit(0);
}

// #define _VAR(val)           NewNode(VAR, (val), NULL, NULL)
// #define _NUM(val)           NewNode(NUM, (val), NULL, NULL)
// #define _OP(op, val1, val2) NewNode(OP, (op), (val1), (val2))

Node* GetN(tokens_t* tokens)
{
    return &tokens->array[(tokens->curr_ptr)++];
}

Node* GetV(tokens_t* tokens)
{
    return &tokens->array[(tokens->curr_ptr)++];
}

Node* GetP(tokens_t* tokens)
{
    if (tokens->array[tokens->curr_ptr].value.op_value == OperatorCode("("))
    {
        (tokens->curr_ptr)++;

        Node* value = GetE(tokens);

        if (tokens->array[tokens->curr_ptr].value.op_value != OperatorCode(")"))
        {
            SyntaxError(tokens, ")");
        }

        (tokens->curr_ptr)++;

        return value;
    }

    if (tokens->curr_ptr < tokens->cnt - 1 &&
        tokens->array[tokens->curr_ptr + 1].value.op_value == OperatorCode("("))
    {
        Node* function = &tokens->array[tokens->curr_ptr];

        tokens->curr_ptr += 2;

        function->left = GetE(tokens);

        if (tokens->array[(tokens->curr_ptr)++].value.op_value != OperatorCode(")"))
        {
            SyntaxError(tokens, ")");
        }

        return function;
    }

    if (tokens->array[tokens->curr_ptr].value.var_value == 'x') return GetV(tokens);

    return GetN(tokens);
}

Node* GetT(tokens_t* tokens)
{
    Node* value = GetP(tokens);

    while (tokens->array[tokens->curr_ptr].value.op_value == OperatorCode("*") ||
           tokens->array[tokens->curr_ptr].value.op_value == OperatorCode("/"))
    {
        Node* _operator = &tokens->array[tokens->curr_ptr];

        (tokens->curr_ptr)++;

        Node* value2 = GetP(tokens);

        _operator->left  = value;
        _operator->right = value2;

        value = _operator;
    }

    return value;
}

Node* GetE(tokens_t* tokens)
{
    Node* value = GetT(tokens);

    while (tokens->array[tokens->curr_ptr].value.op_value == OperatorCode("+") ||
           tokens->array[tokens->curr_ptr].value.op_value == OperatorCode("-"))
    {
        Node* operation = &tokens->array[tokens->curr_ptr];

        (tokens->curr_ptr)++;

        Node* value2 = GetT(tokens);

        operation->left  = value;
        operation->right = value2;

        value = operation;
    }

    return value;
}

Node* GetG(tokens_t* tokens)
{
    Node* value = GetE(tokens);

    if (tokens->array[tokens->curr_ptr].value.op_value != OperatorCode("$")) SyntaxError(tokens, "$");

    (tokens->curr_ptr)++;

    return value;
}

int OperatorCode(const char* _operator)
{
    if (!_operator)
    {
        fprintf(stderr, "OperatorCode() error: null-pointer!\n");
        return -1;
    }

    for (int i = 0; i < OP_CNT; ++i)
    {
        if (strcmp(_operator, operations[i].name) == 0)
        {
            return operations[i].code;
        }
    }

    return 0;
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
//
// #undef _NUM
// #undef _VAR
// #undef _OP
