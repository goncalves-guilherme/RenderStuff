#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram()
{
    const char *vshaderSource =
		"#version 430 \n"
		"void main(void) \n"
		"{ if(gl_VertexID == 0) gl_Position = vec4(0.25, -0.25, 0.0, 1.0); \n"
        "else if(gl_VertexID == 1) gl_Position = vec4(-0.25, -0.25, 0.0, 1.0); \n"
        "else gl_Position = vec4(0.25, 0.25, 0.0, 1.0);}";

    const char *fshaderSource =
		"#version 430 \n"
		"out vec4 color; \n"	
        "void main(void) \n"
		"{ color = vec4(0.0, 1.0, 0.0, 1.0); }";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

void freeMemory()
{
    //glDeleteShader(vShader);
    //glDeleteShader(fShader);  

}

void init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) 
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);
    glPointSize(10);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}

int main()
{
    if (!glfwInit()) { exit(EXIT_FAILURE); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(800, 600, "RenderStuff", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSwapInterval(1);
    init(window);
    while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    cout << "Vomiting Words " << GLFW_JOYSTICK_6 << endl;
}
