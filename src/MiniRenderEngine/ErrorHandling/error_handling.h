#ifndef __ERROR_HANDLING__
#define __ERROR_HANDLING__

#include <GLFW/glfw3.h>
#include <iostream>

void message_log_callback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam);

#endif