.PHONY: build renderer run

run: build main
	@LD_LIBRARY_PATH=./:$(LD_LIBRARY_PATH) ./main

build: renderer
	@clang src/main.c -o main -lGL -L. -lgl_renderer

renderer:
	@clang opengl/gl_backend.c -o libgl_renderer.so -shared
