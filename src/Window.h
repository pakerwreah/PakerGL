#pragma once

#include "Renderer.h"

#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

class GLFWwindow;

namespace PakerGL {

    class Window {
      private:
        std::string m_title;
        GLFWwindow *window;
        std::shared_ptr<Renderer> m_Renderer;

      public:
        Window(const std::string &title, int width, int height);

        void setRenderer(std::shared_ptr<Renderer> renderer);

        void loop(const std::function<void(GLFWwindow *)> &processInput);

        void displayFPS();
    };

}
