#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <shaderClass.h>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>

GLfloat vertices[] =
{
    -0.5f, -0.5f * float(std::sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(std::sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(std::sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(std::sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(std::sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(std::sqrt(3)) / 3, 0.0f // Inner down
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

int main() 
{
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW + GLAD Triangle example", nullptr, nullptr);
    if (!window) 
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, 800, 600);



    Shader shaderProgram("../src/shaders/default.vert", "../src/shaders/default.frag");



    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
