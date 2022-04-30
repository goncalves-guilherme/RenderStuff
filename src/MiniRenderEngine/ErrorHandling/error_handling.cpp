#include "error_handling.h"

void message_log_callback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam)
    {
        std::cout << "OpenGL Error: " << message << std::endl;
    }