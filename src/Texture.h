#pragma once

#include "Types.h"

#include <iostream>
#include <string>
#include <unordered_map>

namespace PakerGL {

    struct Texture {
        int width, height;
        Rect mapCoord;
    };

    class TextureMap {
      private:
        uint textureID;
        std::unordered_map<std::string, Texture> textureMap;

      public:
        explicit TextureMap(const std::unordered_map<std::string, std::string> &paths);
        virtual ~TextureMap();

        void bind(int unit);

        Texture operator[](const std::string &name) const;
    };

}