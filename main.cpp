#include <stdio.h>

#include "ReadExpression.h"
#include "MakeTree.h"
#include "Destroy.h"
#include "Dump.h"

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

    //DrawTree(root, argv[2]);

    ClearBuffer(&buffer);

    TreeDtor(root);

    return 0;
}
