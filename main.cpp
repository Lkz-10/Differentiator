#include <stdio.h>

#include "ReadExpression.h"
#include "MakeTree.h"
#include "Destroy.h"
#include "Dump.h"
#include "Simplifier.h"
#include "Differentiator.h"

int main(const int argc, const char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Enter file name!\n");
        return -1;
    }

    Expression_t buffer = {};

    buffer.string   = ReadExpression(argv[1]);
    buffer.curr_ptr = 0;

    printf("%s\n", buffer.string);

    Node* root = GetG(&buffer);

    Node* d_root = Diff(root);
    data_t result = Eval(root);

    printf("Result: %lg\n", result);
    printf("dResult: %lg\n", Eval(d_root));

    DrawTree(root, argv[2]);
    system("dot Dump.dot -Tpng -o Dump.png");

    DrawTree(d_root, argv[2]);
    system("dot Dump.dot -Tpng -o dDump.png");

    ClearBuffer(&buffer);
    TreeDtor(root);
    TreeDtor(d_root);

    return 0;
}
