#ifndef __DIFF_GLOBALS_H__
#define __DIFF_GLOBALS_H__

const int MAX_LINE_LENGTH = 52;

typedef double data_t;

const data_t POISON = 89173490302;

enum types
{
    NUM = 0,
    VAR = 1,
    OP  = 2
};

enum operations
{
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4
};

struct op_t
{
    char name[MAX_LINE_LENGTH];
    int  code;
};

const int OP_CNT = 4;

const op_t operations[OP_CNT] = {{"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}};

struct Expression_t
{
    char* string;
    int   curr_ptr;
};

union values
{
    double     num_value;
    int        var_value;
    int        op_value;
};

struct Node
{
    int           type;
    union values  value;
    Node*         right;
    Node*         left;
};

#endif
