// X11 window system
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

// opengl
#include <GL/glx.h>
#include <unistd.h>

GLXContext create_glx_context(Display *display, Window window) {
    static int visual_attribs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24,
                                   GLX_DOUBLEBUFFER, None};

    int screen = DefaultScreen(display);
    XVisualInfo *visual_info = glXChooseVisual(display, screen, visual_attribs);
    GLXContext context = glXCreateContext(display, visual_info, NULL, GL_TRUE);
    XFree(visual_info);

    return context;
}

// function to create window
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

int run() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        return -1;
    }

    int width = 800;
    int height = 600;
    Window window = create_window(display, width, height);

    // create the opengl context
    GLXContext context = create_glx_context(display, window);
    glXMakeCurrent(display, window, context);

    // main render loop
    XEvent event;

    while (1) {
        while (XPending(display)) {
            XNextEvent(display, &event);
            if (event.type == Expose) {
                XWindowAttributes gwa;
                XGetWindowAttributes(display, window, &gwa);
                glViewport(0, 0, gwa.width, gwa.height);
            }

            if (event.type == KeyPress) {
                // Exit on any key press
                glXMakeCurrent(display, None, NULL);
                glXDestroyContext(display, context);
                XDestroyWindow(display, window);
                XCloseDisplay(display);
                return 0;
            }
        }

        // opengl rendering code
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glXSwapBuffers(display, window);
        usleep(16000);
    }

    return 0;
}
