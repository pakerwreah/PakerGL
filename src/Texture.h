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
        uint textureID = 0;
        std::unordered_map<std::string, Texture> textureMap;

      public:
        explicit TextureMap(const std::unordered_map<std::string, std::string> &paths);
        virtual ~TextureMap();

        Texture operator[](const std::string &name) const;
    };

}
