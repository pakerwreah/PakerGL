#pragma once

#include "Types.h"

#include <iostream>
#include <string>
#include <unordered_map>

namespace PakerGL {

    class Texture {
      private:
        uint textureID;
        int width, height, channels;
        std::unordered_map<std::string, Rect> coord_map;

      public:
        explicit Texture(const std::unordered_map<std::string, std::string> &paths);
        virtual ~Texture();

        void loadFromFile(const std::string &path);
        void bind(int unit);

        Rect getCoord(const std::string &name) const;
    };

}