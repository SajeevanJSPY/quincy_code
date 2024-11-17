#ifndef __CORE__IO_H
#define __CORE__IO_H

#include "CORE_defines.h"
#include <stdio.h>

CORE_API bool CORE_io_file_read(char **buffer, const char *filename, size_t *size);

#endif // __CORE__IO_H
