#include "Window.h"
#include <iostream>

namespace PakerGL {

    Window::Window(int width, int height) {
        /* Initialize the library */
        if (!glfwInit()) {
            exit(-1);
        }

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(-1);
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) {
            exit(-1);
        }

        std::cout << glGetString(GL_VERSION) << std::endl;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
        glViewport(0, 0, width, height);
    }

    void Window::loop(Renderer &renderer, std::function<void(GLFWwindow *)> processInput) {
        while (!glfwWindowShouldClose(window)) {

            renderer.render();

            glfwSwapBuffers(window);

            glfwPollEvents();

            processInput(window);
        }

        glfwTerminate();
    }

}