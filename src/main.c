#include "../opengl/GL_backend.h"

int main() {
    if (!GL_backend_init()) {
        return -1;
    }

    GL_render_loop();

    // shutdown the opengl
    GL_backend_shutdown();

    return 0;
}
