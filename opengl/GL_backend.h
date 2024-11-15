#ifndef __GL_BACKEND_H
#define __GL_BACKEND_H

#include "GL_defines.h"

// dll exports
#define GL_API

GL_API bool GL_backend_init();
GL_API void GL_render_loop();
GL_API void GL_backend_shutdown();

#endif // __GL_BACKEND_H
