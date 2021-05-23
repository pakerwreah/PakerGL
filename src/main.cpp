#define GLEW_STATIC

#include "Renderer.h"
#include "Shader.h"
#include "Window.h"

using namespace PakerGL;

int main() {
    int width = 640, height = 480;

    Window window("PakerGL", width, height);

    auto renderer = std::make_shared<Renderer>();

    window.setRenderer(renderer);

    auto haunter = std::make_shared<Object>(100, 100, 100, 100);
    auto object1 = std::make_shared<Object>(230, 150, 80, 50);
    auto object2 = std::make_shared<Object>(350, 200, 50, 80);
    auto gastly = std::make_shared<Object>(380, 60, 100, 100);
    auto gengar = std::make_shared<Object>(180, 260, 120, 120);

    renderer->add(haunter);
    renderer->add(object1);
    renderer->add(object2);
    renderer->add(gastly);
    renderer->add(gengar);

    TextureMap textureMap({
        // --
        { "gastly", "res/sprites/gastly.png" },
        { "haunter", "res/sprites/haunter.png" },
        { "gengar", "res/sprites/gengar.png" }
        // --
    });

    haunter->setTexture(textureMap["haunter"]);
    gastly->setTexture(textureMap["gastly"]);
    gengar->setTexture(textureMap["gengar"]);

    Shader shader;
    shader.compile(GL_VERTEX_SHADER, "res/shaders/vertex.vert");
    shader.compile(GL_FRAGMENT_SHADER, "res/shaders/texture.frag");
    shader.link();
    shader.setColor("u_color", { 0.5f, 1.0f, 1.0f, 0.6f });
    shader.setTexture("u_texture", 0);
    shader.setProjection(width, height);
    shader.bind();

    Point gastly_circle_center = gastly->getRect().center();
    constexpr double radius = 20;
    constexpr int steps = 120;
    constexpr double step_angle = 2 * M_PI / steps;
    int gastly_move_step = 0;

    window.loop([&](GLFWwindow *window) {
        // FIXME: Esc not working on Linux =(
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            haunter->moveBy({ -1, 0 });
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            haunter->moveBy({ +1, 0 });
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            haunter->moveBy({ 0, -1 });
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            haunter->moveBy({ 0, +1 });
        }

        const double angle = gastly_move_step * step_angle;
        gastly->moveTo({
            gastly_circle_center.x + radius * cos(angle),
            gastly_circle_center.y + radius * sin(angle),
        });
        gastly_move_step = (gastly_move_step + 1) % steps;
    });

    return 0;
}
