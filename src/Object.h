#pragma once

#include "Texture.h"
#include "Vertex.h"
#include <array>

namespace PakerGL {

    class Object {
      public:
        using Vertices = std::array<Vertex, 6>;

      private:
        Rect m_rect;
        Vertices m_vertices;

      public:
        bool needsUpdate = true;

        Object(float x, float y, float width, float height);
        explicit Object(const Rect &rect);

        Rect getRect() const;

        Vertices getVertices() const;

        void setTexture(const Texture &rect, bool keepAspect = true);

        void resize(const Rect &rect);
        void moveTo(const Point &point);
        void moveBy(const Point &point);
    };

}
