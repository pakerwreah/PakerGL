#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "Renderer.h"

namespace PakerGL {

    class Window {
      private:
        GLFWwindow *window;

      public:
        Window(const std::string &title, int width, int height);

        void loop(Renderer &renderer, std::function<void(GLFWwindow *)> processInput);
    };

}