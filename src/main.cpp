#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <iostream>

#include "Shader.h"
#include "VertexBuffer.h"

using namespace PakerGL;

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;

    struct Vertex {
        float x, y;
        float color[4];

        Vertex(const float &x, const float &y, const float color[4]) {
            this->x = x;
            this->y = y;
            std::memcpy(this->color, color, 4 * sizeof(float));
        }
    };

    float color1[4] = { 1.0f, 0.5f, 0.2f, 1.0f };
    float color2[4] = { 0.0f, 0.5f, 0.2f, 1.0f };

    Vertex vertexData[] = {
        { -0.5f, -0.5f, color1 },
        { 0.5f, -0.5f, color2 },
        { 0.0f, 0.5f, color1 }
    };

    VertexBuffer object(vertexData, sizeof(vertexData));
    Shader shader("res/shaders/FlatColor.glsl");

    object.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));

    shader.bind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}