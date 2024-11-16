#include "GL_shader.h"

#include <core/CORE_io.h>

#include <stdio.h>
#include <string.h>
#include <time.h>

// utility function for checking the shader compile errors
void check_compile_errors(GLuint shader, const char *type);

bool shader_program_init(shader *shader) {
    // ------------------ vertex shader ------------------
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertex_source =
        (const GLchar *)CORE_io_file_read(shader->vertex_shader_path, NULL);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    check_compile_errors(vertex_shader, "VERTEX");

    // ------------------ fragment shader ------------------
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *frag_source =
        (const GLchar *)CORE_io_file_read(shader->frag_shader_path, NULL);
    glShaderSource(fragment_shader, 1, &frag_source, NULL);
    glCompileShader(fragment_shader);
    check_compile_errors(fragment_shader, "FRAGMENT");

    // ------------------ shader program ------------------
    shader->shader_program = glCreateProgram();
    glAttachShader(shader->shader_program, vertex_shader);
    glAttachShader(shader->shader_program, fragment_shader);
    glLinkProgram(shader->shader_program);
    check_compile_errors(shader->shader_program, "PROGRAM");

    // after linked the shaders, delete them
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // set VBO and VAO
	float vertices[] = {
        0.0f,  0.5f, 0.0f,  // Top
       -0.5f, -0.5f, 0.0f,  // Bottom left
        0.5f, -0.5f, 0.0f   // Bottom right
    };
    glGenVertexArrays(1, &shader->VAO);
	glBindVertexArray(shader->VAO);

    // bind buffers
    glGenBuffers(1, &shader->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, shader->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
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
void check_compile_errors(GLuint shader, const char *type) {
    GLint success;
    GLchar info_log[1024];
    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, info_log);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type,
                   info_log);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, info_log);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type,
                   info_log);
        }
    }
}
