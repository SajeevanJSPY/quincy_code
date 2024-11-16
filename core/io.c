#include "core/CORE_io.h"

#include <stdlib.h>

char *CORE_io_file_read(const char *filename, size_t *size) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("failed to load the file\n");
        exit(-1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // stack file size allocated to the file read,
    // if the file size exceeds this we dynamically allocate the memory
    char char_buffer[FILE_READ_STACK_SIZE];

    if (file_size < 0) {
        perror("Failed to determine file size");
        fclose(file);
        exit(-1);
    }

    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        perror("Failed to allocate buffer");
        fclose(file);
        return NULL;
    }
    // Read the file into the buffer
    size_t read_size = fread(buffer, 1, file_size, file);
    if (read_size != file_size) {
        perror("Failed to read file");
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[file_size] = '\0';

    fclose(file);

    if (size) {
        *size = file_size;
    }

    return buffer;
}
