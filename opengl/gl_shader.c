#include "GL_shader.h"
#include <core/CORE_io.h>

#include <stdio.h>
#include <string.h>
#include <time.h>

// utility function for checking the shader compile errors
bool check_compile_errors(GLuint shader, const char *type);

bool shader_program_init(shader *shader) {
    // ------------------ vertex shader ------------------
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    char *vertex_buffer;
    if (!CORE_io_file_read(&vertex_buffer, shader->vertex_shader_path, NULL)) {
        return false;
    }
    const GLchar *vertex_source = (const GLchar *)vertex_buffer;
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    if (!check_compile_errors(vertex_shader, "VERTEX")) {
        LOG_ERROR("failed to compile the vertex shader");
        return false;
    }

    // ------------------ fragment shader ------------------
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    char *frag_buffer;
    if (!CORE_io_file_read(&frag_buffer, shader->frag_shader_path, NULL)) {
        return false;
    }
    const GLchar *frag_source = (const GLchar *)frag_buffer;
    glShaderSource(fragment_shader, 1, &frag_source, NULL);
    glCompileShader(fragment_shader);
    if (!check_compile_errors(fragment_shader, "FRAGMENT")) {
        LOG_ERROR("failed to compile the fragment shader");
        return false;
    }

    // ------------------ shader program ------------------
    shader->shader_program = glCreateProgram();
    glAttachShader(shader->shader_program, vertex_shader);
    glAttachShader(shader->shader_program, fragment_shader);
    glLinkProgram(shader->shader_program);
    if (!check_compile_errors(shader->shader_program, "PROGRAM")) {
        LOG_ERROR("failed to compile the shader program");
        return false;
    }

    // after linked the shaders, delete them
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // set VBO and VAO
    float vertices[] = {
        0.0f,  0.5f,  0.0f, // Top
        -0.5f, -0.5f, 0.0f, // Bottom left
        0.5f,  -0.5f, 0.0f  // Bottom right
    };
    glGenVertexArrays(1, &shader->VAO);
    glBindVertexArray(shader->VAO);

    // bind buffers
    glGenBuffers(1, &shader->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, shader->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.2f);

    glBindVertexArray(shader->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    return true;
}

// @param: type - "PROGRAM" | "SHADER"
bool check_compile_errors(GLuint shader, const char *type) {
    GLint success;
    GLchar info_log[1024];
    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, info_log);
            INFO("%s", info_log);
            return false;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, info_log);
            INFO("%s", info_log);
            return false;
        }
    }

    return true;
}
