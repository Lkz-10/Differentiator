#include "ReadExpression.h"

int ReadExpression(const char* file_name, Expression_t* buffer)
{
    FILE* file_ptr = fopen(file_name, "rb");

    if (!file_ptr)
    {
        fprintf(stderr, "File error!\n");
        return NULL;
    }

    if (fseek(file_ptr, 0, SEEK_END) != 0)
    {
        fprintf(stderr, "fseek() error!\n");

        fclose(file_ptr);
        return NULL;
    }

    buffer->size = ftell(file_ptr);
    //fprintf(stderr, "buf_size: %ld\n", buf_size);

    rewind(file_ptr);

    buffer->string = (char*) calloc(1, buffer->size + 1);

    if (!buffer)
    {
        fprintf(stderr, "Memory error!\n");

        fclose(file_ptr);
        return NULL;
    }

    if ((long int) fread(buffer->string, sizeof(char), buffer->size, file_ptr) < buffer->size - 1)
    {
        fprintf(stderr, "Reading error!\n");

        fclose(file_ptr);
        free  (buffer);

        return NULL;
    }

    fclose(file_ptr);

    return 0;
}
