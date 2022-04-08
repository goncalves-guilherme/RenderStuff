#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

GLuint renderingProgram;
unsigned int VBO, VAO;

GLuint createShaderProgram()
{
    const char *vshaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}";

    const char *fshaderSource =
		"#version 430 \n"
		"out vec4 color; \n"	
        "void main(void) \n"
		"{ color = vec4(0.0, 1.0, 0.0, 1.0); }";

    // Creates Vertex Shader
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glCompileShader(vShader);
    
    // Error Checking
    int success;
    char infoLog[512];
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Creates Vertex Shader
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    glCompileShader(fShader);

    // Error Checking
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link both shaders into a called program
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    // Check for linking errors
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(vfProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Opengl suggest to clean fragment and vertext shader when linked to a program
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return vfProgram;
}

void addVerticeArrayBuffers()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    // Generate vertice array buffers. VAO & VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}

void freeResources()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(renderingProgram);
}

void init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram();
}

void messageLogCallback(
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

int main()
{
    if (!glfwInit()) { exit(EXIT_FAILURE); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RenderStuff", NULL, NULL);

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

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glfwSwapInterval(1);

    init(window);

    // Set Debug Handler
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(&messageLogCallback, 0);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    addVerticeArrayBuffers();

    while (!glfwWindowShouldClose(window)) 
    {
		
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(renderingProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    freeResources();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    cout << "Vomiting Words " << GLFW_JOYSTICK_6 << endl;
}
