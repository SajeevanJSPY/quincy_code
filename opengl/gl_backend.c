#include "opengl/GL_backend.h"
#include "opengl/GL_shader.h"
#include "opengl/GL_window.h"

#include <stdlib.h>

// window management
void *window_context;
shader *shader_info;

bool GL_backend_init() {
    LOG_TRACE("Init: Window");
    if (!GL_window_create(&window_context)) {
        LOG_ERROR("failed to create window");
        return false;
    }

    // initializing the opengl graphics api
    if (gladLoadGL() < 1) {
        LOG_ERROR("failed to load the glad opengl function pointers");
        return false;
    }

    shader_info = malloc(sizeof(shader));
    if (!shader_info) {
        LOG_ERROR("memory allocation failed");
        return false;
    }
    shader_info->vertex_shader_path = "shaders/simple.vert";
    shader_info->frag_shader_path = "shaders/simple.frag";

    // simple triangle program
    LOG_TRACE("Init: Shader Program");
    if (!shader_program_init(shader_info)) {
        LOG_ERROR("shader program init failed");
        return false;
    }

    return true;
}

void loop() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.2f, 0.6f, 0.2f);

    glBindVertexArray(shader_info->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GL_render_loop() {
    void (*loop_ptr)() = &loop;

    GL_window_loop(window_context, loop_ptr);
}

void GL_backend_shutdown() {}
