#include "Window.h"
#include "debug.h"
#include <sstream>

namespace PakerGL {

    Window::Window(const std::string &title, int width, int height) : m_title(title) {

        if (!glfwInit()) {
            std::cerr << "GLFW failed to initialize." << std::endl;
            exit(-1);
        }

        glfwSetErrorCallback([](int code, const char *error) {
            std::cerr << "[" << code << "] " << error << std::endl;
        });

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) {
            exit(-1);
        }

        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    void Window::setRenderer(std::shared_ptr<Renderer> renderer) {
        m_Renderer = std::move(renderer);
    }

    void Window::displayFPS() {
        static int frames = 0;
        static double lastTime = 0;
        double currentTime = glfwGetTime();
        frames++;
        if (currentTime - lastTime >= 1.0) {
            std::ostringstream ss;
            ss << m_title << " (" << frames << " fps)";
            glfwSetWindowTitle(window, ss.str().c_str());
            frames = 0;
            lastTime = currentTime;
        }
    }

    void Window::loop(const std::function<void(GLFWwindow *)> &processInput) {
        while (!glfwWindowShouldClose(window)) {

            m_Renderer->render();

            glfwSwapBuffers(window);

            glfwPollEvents();

            processInput(window);

            checkErrors();

            displayFPS();
        }

        glfwTerminate();
    }

}
