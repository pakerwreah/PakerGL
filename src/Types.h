#pragma once

#include <glm/vec2.hpp>

namespace PakerGL {

    typedef glm::vec2 Point;

    struct Rect {
        float x, y, width, height;

        inline Point origin() const {
            return { x, y };
        }

        inline Point end() const {
            return { x + width, y + height };
        }

        inline Point center() const {
            return { x + width / 2, y + height / 2 };
        }
    };

    struct Color {
        float red, green, blue, alpha;
    };

}
