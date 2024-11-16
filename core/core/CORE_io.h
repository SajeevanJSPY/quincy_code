#ifndef __CORE__IO_H
#define __CORE__IO_H

#include "CORE_defines.h"
#include <stdio.h>


#define FILE_READ_STACK_SIZE 1024

CORE_API char *CORE_io_file_read(const char *filename, size_t *size);

#endif // __CORE__IO_H
