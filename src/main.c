#include "../opengl/GL_backend.h"
#include <core/CORE_logger.h>

#include <stdio.h>

/*
        Application Subsystem
                make sure every subsystem must initialized in a certain order
   and shutdown them in the reverse order

                memory
                logger
                renderer (opengl)
*/

int main() {
    CORE_logger_init(LOG_ERROR, NULL);

    if (!GL_backend_init()) {
        return -1;
    }

    GL_render_loop();

    // shutdown the opengl
    GL_backend_shutdown();

    CORE_logger_shutdown();

    return 0;
}
