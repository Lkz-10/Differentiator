#include "DifferentiatorHeaders.h"

int main(const int argc, const char** argv)
{
    if (CheckArgc(argc) != OK) return ERROR;

    Expression_t buffer = {};
    ReadExpression(argv[1], &buffer);

    tokens_t tokens = {};
    TokensCtor(&tokens, buffer.size);

    FillTokens(&tokens, &buffer);

    Node* root   = GetG(&tokens);
    Node* d_root = Diff(root);

//     data_t result = Eval(root);
//     printf("Result: %lg\n", result);

    DrawTree(root, argv[2]);
    system("dot Dump.dot -Tpng -o Dump.png");

    DrawTree(d_root, argv[2]);
    system("dot Dump.dot -Tpng -o dDump.png");

    Simplify(d_root);

    DrawTree(d_root, argv[2]);
    system("dot Dump.dot -Tpng -o dDump2.png");

    WriteExpression(root, d_root, argv[3]);

    ClearBuffer (&buffer);
    TokensDtor  (&tokens);
    TreeDtor    (d_root);

    return 0;
}
