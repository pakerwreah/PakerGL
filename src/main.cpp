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

    auto object1 = std::make_shared<Object>(100, 100, 100, 100);
    auto object2 = std::make_shared<Object>(230, 150, 80, 50);
    auto object3 = std::make_shared<Object>(350, 200, 50, 80);
    auto object4 = std::make_shared<Object>(380, 60, 100, 100);
    auto object5 = std::make_shared<Object>(180, 260, 120, 120);

    renderer->add(object1);
    renderer->add(object2);
    renderer->add(object3);
    renderer->add(object4);
    renderer->add(object5);

    TextureMap textureMap({
        // --
        { "gastly", "res/sprites/gastly.png" },
        { "haunter", "res/sprites/haunter.png" },
        { "gengar", "res/sprites/gengar.png" }
        // --
    });

    Texture haunter = textureMap["haunter"];
    Texture gastly = textureMap["gastly"];
    Texture gengar = textureMap["gengar"];

    object1->setTexture(haunter);
    object4->setTexture(gastly);
    object5->setTexture(gengar);

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
