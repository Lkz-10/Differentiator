#include "ReadExpression.h"

char* ReadExpression(const char* file_name)
{
    FILE* file_ptr = fopen(file_name, "r");

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

    long int buf_size = ftell(file_ptr);
    fprintf(stderr, "buf_size: %ld\n", buf_size);

    rewind(file_ptr);

    char* buffer = (char*) calloc(1, buf_size + 1);

    if (!buffer)
    {
        fprintf(stderr, "Memory error!\n");

        fclose(file_ptr);
        return NULL;
    }

    if ((long int) fread(buffer, sizeof(char), buf_size, file_ptr) < buf_size - 1)
    {
        fprintf(stderr, "Reading error!\n");

        fclose(file_ptr);
        free  (buffer);

        return NULL;
    }

    fclose(file_ptr);

    return buffer;
}
