#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex Shader Source Code
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";

// Fragment Shader Source Code
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Orange color
}
)";

// Function to compile shaders
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << std::endl;
        return 0; // Return 0 to indicate failure
    }
    return shader;
}

// Function to link shaders into a program
GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (vertexShader == 0 || fragmentShader == 0) {
        return 0; // Return 0 if shader compilation failed
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking error: " << infoLog << std::endl;
        return 0; // Return 0 to indicate failure
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// Function to handle window resizing
void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

// Function to handle input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Global variables for shader program and VAO
GLuint shaderProgram;
GLuint VAO;

void update(){
    // Update game logic here
}

void render(){
    // Clear the color buffer
    glClearColor(0.9f, 0.5f, 0.9f, 1.0f); // Pink like fucking Barbie 
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Game loop setup", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the viewport size
    glViewport(0, 0, 800, 600);

    // Set the callback for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Define vertex data for a triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom-left vertex
         0.5f, -0.5f, 0.0f, // Bottom-right vertex
         0.0f,  0.5f, 0.0f  // Top vertex
    };

    // Create a Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // Bind the VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Specify how OpenGL should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create the shader program
    shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    if (shaderProgram == 0) {
        std::cerr << "Failed to create shader program" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Handle input
        processInput(window);

        update();

        render();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Clean up
    glfwTerminate();
    return 0;
}