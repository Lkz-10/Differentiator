#include "Destroy.h"

int TreeDtor(Node* node)
{
    if (!node) return 0;

    TreeDtor(node->left);
    TreeDtor(node->right);

    free(node);
    node = NULL;

    return 0;
}

int ClearNode(Node* node)
{
    if (!node) return 0;

    free(node);

    node = NULL;

    return 0;
}

int ClearBuffer(Expression_t* buffer)
{
    free(buffer->string);
    buffer->string = NULL;

    buffer->curr_ptr = 0;
    buffer->size     = 0;

    return 0;
}
