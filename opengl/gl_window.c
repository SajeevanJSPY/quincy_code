#include "GL_window.h"

// X11 window system
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

// opengl
#include <GL/glx.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	Display *display;
	Window window;
	GLXContext glx_context;
} window_context;

GLXContext create_glx_context(Display *display, Window window);
Window create_window(Display *display, int width, int height);

bool GL_window_create(void **win_context) {
	*win_context = malloc(sizeof(window_context));

    window_context *context = (window_context *)*win_context;
    context->display = XOpenDisplay(NULL);
    if (!context->display) {
        return -1;
    }

	int width = 800;
    int height = 600;
    context->window = create_window(context->display, width, height);

    // create the opengl context
    context->glx_context = create_glx_context(context->display, context->window);
    glXMakeCurrent(context->display, context->window, context->glx_context);

	return true;
}

// main render loop
void GL_window_loop(void *win_context) {
    window_context *context = (window_context *)win_context;
	if (!context) {
		printf("failed to get the window context\n");
		return;
	}
    XEvent event;

    while (1) {
        while (XPending(context->display)) {
            XNextEvent(context->display, &event);
            if (event.type == Expose) {
                XWindowAttributes gwa;
                XGetWindowAttributes(context->display, context->window, &gwa);
                glViewport(0, 0, gwa.width, gwa.height);
            }

            if (event.type == KeyPress) {
                // Exit on any key press
                glXMakeCurrent(context->display, None, NULL);
                glXDestroyContext(context->display, context->glx_context);
                XDestroyWindow(context->display, context->window);
                XCloseDisplay(context->display);
                return;
            }
        }

        // opengl rendering code
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glXSwapBuffers(context->display, context->window);
        usleep(16000);
    }

}

void GL_window_destroy(void *context) {
}

GLXContext create_glx_context(Display *display, Window window) {
    static int visual_attribs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24,
                                   GLX_DOUBLEBUFFER, None};

    int screen = DefaultScreen(display);
    XVisualInfo *visual_info = glXChooseVisual(display, screen, visual_attribs);
    GLXContext context = glXCreateContext(display, visual_info, NULL, GL_TRUE);
    XFree(visual_info);

    return context;
}

Window create_window(Display *display, int width, int height) {
    int screen = DefaultScreen(display);
    Window root_window = RootWindow(display, screen);
    XSetWindowAttributes swa;
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    Window window = XCreateWindow(display, root_window, 0, 0, width, height, 0,
                                  CopyFromParent, InputOutput, CopyFromParent,
                                  CWEventMask, &swa);
    XMapWindow(display, window);
    XStoreName(display, window, "Quincy Code");

    return window;
}
