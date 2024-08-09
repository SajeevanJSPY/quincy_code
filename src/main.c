#include "../opengl/GL_backend.h"

#include <stdio.h>

int main() {
    if (!GL_backend_init()) {
        return -1;
    }

    printf("hello quincy code\n");

    return 0;
}