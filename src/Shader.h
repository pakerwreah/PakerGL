#pragma once

#include "Types.h"

#include <iostream>
#include <string>
#include <vector>

namespace PakerGL {

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

        void setColor(const std::string &name, const Color &color);

        void setTexture(const std::string &name, int unit);

        void compile(uint type, const std::string &filepath);

        void link();
    };

}