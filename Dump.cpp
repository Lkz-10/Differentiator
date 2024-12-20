#include "Dump.h"
#include <assert.h>

int DrawTree(Node* root, const char* file_name)
{
    if (!root || !file_name)
    {
        fprintf(stderr, "Drawing error: root(%p), file(%s)\n", root, file_name);
        return -1;
    }

    FILE* file_ptr = fopen(file_name, "w");
    //fprintf(file_ptr, "Zenit champion!\n");

    if (!file_ptr)
    {
        fprintf(stderr, "File \"%s\" error!\n", file_name);
        return -1;
    }

    fprintf(file_ptr, "digraph G\n{\n  rankdir = UD;\n  edge[color = \"green\"];\n");

    DrawNode(root, file_ptr);

    fprintf(file_ptr, "}");

    fclose(file_ptr);

    return 0;
}

int DrawNode(Node* node, FILE* file_ptr)
{
    if (!node) return 0;

    if (!file_ptr)
    {
        fprintf(stderr, "File error!\n");
        return -1;
    }

    fprintf(file_ptr, "  \"%5p\" [shape = Mrecord, ", node);

    switch (node->type)
    {
        case NUM:
        {
            fprintf(file_ptr, "color = \"darkblue\", style = \"filled\", fillcolor = \"lightcyan\", "
                    "fontcolor = \"darkblue\", ");

            break;
        }

        case VAR:
        {
            fprintf(file_ptr, "color = \"darkorange4\", style = \"filled\", fillcolor = \"lemonchiffon\", "
                    "fontcolor = \"darkorange4\", ");

            break;
        }

        case OP:
        {
            fprintf(file_ptr, "color = \"darkgreen\", style = \"filled\", fillcolor = \"darkolivegreen1\", "
                    "fontcolor = \"darkgreen\", ");

            break;
        }

        default:
        {
            fprintf(stderr, "Error: wrong node type!(%d)\n", node->type);
            return ERROR;
        }
    }

    fprintf(file_ptr, "label = \"{%p | type = %d | ", node, node->type);

    if (node->type == NUM)
    {
        fprintf(file_ptr, "%lg}", node->value.num_value);
    }
    else if (node->type == VAR)
    {
        fprintf(file_ptr,  "x}");
    }
    else
    {
        for (int i = 0; i < OP_CNT; ++i)
        {
            if (node->value.op_value == operations[i].code)
            {
                fprintf(file_ptr, "%s}", operations[i].name);
                break;
            }
        }
    }

    fprintf(file_ptr, "\"];\n");

    if (DrawNode(node->left,  file_ptr) != 0) return -1;
    if (DrawNode(node->right, file_ptr) != 0) return -1;

    if (node->left)
    {
        fprintf(file_ptr, "  \"%5p\" -> \"%5p\";\n", node, node->left);
    }

    if (node->right)
    {
        fprintf(file_ptr, "  \"%5p\" -> \"%5p\";\n", node, node->right);
    }

    return 0;
}

