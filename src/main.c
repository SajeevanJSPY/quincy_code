#include <core/CORE_logger.h>
#include <opengl/GL_backend.h>

/*
        Application Subsystem
                make sure every subsystem must initialized in a certain order
   and shutdown them in the reverse order

                memory
                logger
                renderer (opengl)
*/

int main() {
    CORE_logger_init(LOG_FATAL, "output/log");
    LOG_TRACE("Init: Application");

    LOG_TRACE("Init: Renderer Backend");
    if (!GL_backend_init()) {
        LOG_FATAL("Renderer Backend");
        return -1;
    }

    LOG_TRACE("Init: Renderer Loop");
    GL_render_loop();

    LOG_TRACE("Shutdown: Renderer Backend");
    GL_backend_shutdown();

    CORE_logger_shutdown();

    return 0;
}
