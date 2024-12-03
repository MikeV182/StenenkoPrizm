#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <shaderClass.h>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>

// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS             //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

GLuint indices[] = 
{
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right truangle
    5, 4, 1 // Upper triangle
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() 
{
    // Initializing GLFW
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Hints for GLFW to know what version of OpenGL to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // using Core profile to use latest OpenGL functions

    // Creating window to work with
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW + GLAD Triangle example", nullptr, nullptr);
    if (!window) 
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // callback function will be called when window is changed in size

    // Loading GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Viewport from bottom left corner to upper right corner
    glViewport(0, 0, 800, 600);

    // Initializing shader program
    Shader shaderProgram("../src/shaders/default.vert", "../src/shaders/default.frag");

    // Creating Vertex Array Object and binding it
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));   // Initializing Vertex Buffer Object
    EBO EBO1(indices, sizeof(indices));     // Initializing Element Buffer Object

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();          // Unbinding Objects, so that we can't change them by accident
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); // Getting the reference of uniform variable
                                                                    // and storing it into GLuint variable

    // Main rendering cycle
    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window); // Input control for out window

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // specifying the color to clear a window with
        glClear(GL_COLOR_BUFFER_BIT); // entire color buffer will be filled with specified color in 'glClearColor'

        shaderProgram.Activate();
        glUniform1f(uniID, 0.5f);
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // drawing 9 vertices with primitive of GL_TRIANGLES

        glfwPollEvents(); // Polling events such as opening it, resizing, etc.
        glfwSwapBuffers(window); // swapping front and back buffers
    }

    // Deleting objects from memory and terminating current window
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
