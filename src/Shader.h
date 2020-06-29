#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace PakerGL {

    struct Color {
        float red, green, blue, alpha;
    };

    class Shader {
      private:
        uint m_RendererID;
        std::vector<uint> shaders;

      public:
        Shader();
        virtual ~Shader();

        void bind() const;
        void unbind() const;

        void setProjection(int width, int height);

        void setColor(const std::string &name, Color color);

        void compile(uint type, const std::string &filepath);

        void link();
    };

}