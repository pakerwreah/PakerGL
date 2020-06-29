#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include "Renderer.h"
#include "Shader.h"
#include "Window.h"
#include "debug.h"

using namespace PakerGL;

int main() {
    int width = 640, height = 480;
    Window window("PakerGL", width, height);
    Renderer renderer;

    renderer.add(std::make_shared<Object>(150, 100, 50, 50));
    renderer.add(std::make_shared<Object>(250, 150, 80, 50));
    renderer.add(std::make_shared<Object>(400, 200, 50, 80));

    Shader shader;
    shader.compile(GL_VERTEX_SHADER, "res/shaders/position.vert");
    shader.compile(GL_FRAGMENT_SHADER, "res/shaders/color.frag");
    shader.link();
    shader.setColor("color", { 0.5f, 1.0f, 1.0f, 0.6f });
    shader.setProjection(width, height);
    shader.bind();

    window.loop(renderer, [](GLFWwindow *window) {
        // FIXME: Esc not working on Linux =(
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    });

    return 0;
}