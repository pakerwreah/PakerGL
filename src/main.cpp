#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include "Shader.h"
#include "Window.h"
#include "Renderer.h"

using namespace PakerGL;

int main() {
    Window window(640, 480);
    Renderer renderer;

    renderer.add(std::make_shared<Object>(0, 10, 50, 50));
    renderer.add(std::make_shared<Object>(100, 50, 80, 50));
    renderer.add(std::make_shared<Object>(250, 100, 50, 80));

    Shader shader("res/shaders/FlatColor.glsl");
    shader.setColor("u_color", { 0.5, 1.0f, 1.0f, 0.6f });
    shader.bind();

    window.loop(renderer, [](GLFWwindow *window) {
        // FIXME: Esc not working on Linux =(
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    });

    return 0;
}