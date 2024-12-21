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
    DIV = 4,
    POW = 5,
    SIN = 6,
    COS = 7,
    LN  = 11
};

struct op_t
{
    char name[MAX_LINE_LENGTH];
    int  code;
};

const int OP_CNT = 11;

const op_t operations[OP_CNT] = {{"+", 1},   {"-", 2},   {"*", 3}, {"/", 4}, {"^", 5},
                                 {"sin", 6}, {"cos", 7}, {"(", 8}, {")", 9}, {"$", 10},
                                 {"ln", 11}};

struct Expression_t
{
    char* string;
    int   curr_ptr;
    int   size;
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

struct tokens_t
{
    int   cnt;
    int   size;
    int   curr_ptr;
    Node* array;
};

enum return_codes
{
    ERROR = -1,
    OK    = 0
};

#endif
