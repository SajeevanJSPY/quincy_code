.PHONY: build renderer run

GL_LIBS := -lGL
X11_LIBS := -lX11
RENDERER_DLL := -L ./output -lgl_renderer -lcore
INCLUDE := -Iexternal/include

run: build output/main
	@LD_LIBRARY_PATH=./output:$(LD_LIBRARY_PATH) ./output/main

build: renderer core
	@clang src/main.c external/glad/glad.c -o ./output/main ${GL_LIBS} ${RENDERER_DLL} ${INCLUDE}

renderer:
	@clang opengl/*.c -o output/libgl_renderer.so -shared -fPIC ${INCLUDE}

core:
	@clang core/*.c -o output/libcore.so -shared

format:
	@clang-format -i **/*.c
	@clang-format -i **/*.h

clean:
	@rm output/*
