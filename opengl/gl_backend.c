#include "GL_backend.h"
#include "GL_shader.h"
#include "GL_window.h"

#include <stdio.h>
#include <stdlib.h>

static void *window_context;

bool GL_backend_init() {
	// window creation
	if (!GL_window_create(&window_context)) {
		return false;
	}

	// initializing the opengl graphics api
	int version = gladLoadGL();
	if (version < 1) {
		printf("failed to load the glad opengl apis");
		return false;
	}

	shader *shader;
	shader = malloc(sizeof(*shader));
	if (!shader) {
		printf("memory allocation failed'\n");
		return false;
	}
	shader->vertex_shader_path = "shaders/simple.vert";
	shader->frag_shader_path = "shaders/simple.frag";
	// simple triangle program
	if (!shader_program_init(shader)) {
		printf("shader program init failed\n");
		return false;
	}

	return true;
}

void GL_render_loop() {
}

void GL_backend_shutdown() {

}
