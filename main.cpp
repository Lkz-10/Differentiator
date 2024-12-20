#include <stdio.h>

#include "ReadExpression.h"
#include "MakeTree.h"
#include "Destroy.h"
#include "Dump.h"
#include "Simplifier.h"
#include "Differentiator.h"
#include "LexicalAnalysis_diff.h"

int main(const int argc, const char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Enter file name!\n");
        return -1;
    }

    Expression_t buffer = {};

    ReadExpression(argv[1], &buffer);

    printf("Expression: %s\n", buffer.string);

    tokens_t tokens = {};

    TokensCtor(&tokens, buffer.size);

    FillTokens(&tokens, &buffer);

    Node* root = GetG(&tokens);

    Node* d_root = Diff(root);

//     data_t result = Eval(root);
//
//     printf("Result: %lg\n", result);
//     printf("dResult: %lg\n", Eval(d_root));

    DrawTree(root, argv[2]);
    system("dot Dump.dot -Tpng -o Dump.png");

    DrawTree(d_root, argv[2]);
    system("dot Dump.dot -Tpng -o dDump.png");

    Simplify(d_root);

    DrawTree(d_root, argv[2]);
    system("dot Dump.dot -Tpng -o dDump2.png");

    ClearBuffer(&buffer);
    TokensDtor(&tokens);
    TreeDtor(d_root);

    return 0;
}
