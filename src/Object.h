#pragma once

#include "Texture.h"
#include "Vertex.h"

namespace PakerGL {

    class Object {
      private:
        Rect m_rect;
        Vertex vertexData[6];

      public:
        bool needsUpdate = true;

        Object(float x, float y, float width, float height);
        explicit Object(const Rect &rect);

        const Vertex *getVertices() const;

        size_t getSize() const;

        void setTexture(const Texture &rect, bool keepAspect = true);

        void resize(const Rect &rect);
    };

}
