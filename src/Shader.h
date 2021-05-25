#pragma once

#include "Types.h"

#include <iostream>
#include <string>
#include <vector>

namespace PakerGL {

    class Shader {
      private:
        uint m_program;
        std::vector<uint> shaders;

      public:
        Shader();
        virtual ~Shader();

        void bind() const;
        static void unbind();

        void setProjection(int width, int height) const;

        void setColor(const std::string &name, const Color &color) const;

        void setTexture(const std::string &name, int unit) const;

        void compile(uint type, const std::string &filepath);

        void link();
    };

}
