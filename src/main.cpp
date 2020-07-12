#define GLEW_STATIC

#include "Renderer.h"
#include "Shader.h"
#include "Window.h"
#include "debug.h"

using namespace PakerGL;

int main() {
    int width = 640, height = 480;

    Window window("PakerGL", width, height);

    auto renderer = std::make_shared<Renderer>();

    window.setRenderer(renderer);

    auto object1 = std::make_shared<Object>(150, 100, 50, 50);
    auto object2 = std::make_shared<Object>(250, 150, 80, 50);
    auto object3 = std::make_shared<Object>(400, 200, 50, 80);
    auto object4 = std::make_shared<Object>(200, 250, 120, 120);

    renderer->add(object1);
    renderer->add(object2);
    renderer->add(object3);
    renderer->add(object4);

    Texture texture({ { "gastly", "res/sprites/gastly.png" } });

    Rect texCoord = texture.getCoord("gastly");

    object1->setTexture(texCoord);
    object4->setTexture(texCoord);

    Shader shader;
    shader.compile(GL_VERTEX_SHADER, "res/shaders/vertex.vert");
    shader.compile(GL_FRAGMENT_SHADER, "res/shaders/texture.frag");
    shader.link();
    shader.setColor("u_color", { 0.5f, 1.0f, 1.0f, 0.6f });
    shader.setTexture("u_texture", 0);
    shader.setProjection(width, height);
    shader.bind();

    window.loop([](GLFWwindow *window) {
        // FIXME: Esc not working on Linux =(
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    });

    return 0;
}