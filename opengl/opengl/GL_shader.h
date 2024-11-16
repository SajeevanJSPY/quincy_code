#ifndef __GL_SHADER_H
#define __GL_SHADER_H

#include "GL_defines.h"

// shader utility data structure
typedef struct {
    char *vertex_shader_path;
    char *frag_shader_path;

    // vertex array and buffer info
    GLuint VBO;
    GLuint VAO;
    GLuint shader_program;
} shader;

typedef struct {
    GLuint VAO;
    GLuint *VBO;
    GLuint shader_program;
} vertex_buffers;

bool shader_program_init(shader *shader);

#endif // __GL_SHADER_H
