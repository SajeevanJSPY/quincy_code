#include "core/CORE_io.h"
#include "core/CORE_logger.h"

#include <stdlib.h>

bool CORE_io_file_read(char **buffer, const char *filename, size_t *file_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        LOG_ERROR("failed to load the file");
        return false;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (size < 0) {
        LOG_ERROR("Failed to determine file size");
        goto close;
    }
    *buffer = malloc(size + 1);
    if (!buffer) {
        LOG_ERROR("Failed to allocate buffer");
        goto close;
    }
    // Read the file into the buffer
    size_t read_size = fread(*buffer, 1, size, file);
    if (read_size != size) {
        LOG_ERROR("Failed to read file");
        free(buffer);
        goto close;
    }
    (*buffer)[size] = '\0';

    if (file_size)
        *file_size = size;

    return true;

close:
    fclose(file);
    return false;
}
