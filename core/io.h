#ifndef __CORE__IO_H
#define __CORE__IO_H

#include <stdio.h>

#define CORE_API

#define FILE_READ_STACK_SIZE 1024

CORE_API char *read_file(const char *filename, size_t *size);

#endif // __CORE__IO_H
