.PHONY: build renderer run

GL_LIBS := -lGL
X11_LIBS := -lX11
RENDERER_DLL := -L ./output -lgl_renderer -lcore
CORE_INCLUDE := -Icore/include
INCLUDE := -Iexternal/include -Iopengl ${CORE_INCLUDE}

run: build output/main
	@LD_LIBRARY_PATH=./output:$(LD_LIBRARY_PATH) ./output/main

build: pre-setup renderer engine_core
	@clang src/main.c external/glad/glad.c -o ./output/main ${GL_LIBS} ${RENDERER_DLL} ${INCLUDE}

renderer:
	@clang opengl/*.c -o output/libgl_renderer.so -shared -fPIC ${INCLUDE}

engine_core:
	@clang core/*.c -o output/libcore.so -shared ${CORE_INCLUDE}

pre-setup:
	@mkdir -p output

format:
	@clang-format -i **/*.c
	@clang-format -i **/*.h

clean:
	@rm output/*
