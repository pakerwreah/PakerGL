#pragma once

#include "Texture.h"
#include "Vertex.h"

namespace PakerGL {

    class Object {
      private:
        Vertex vertexData[6];

      public:
        bool needsUpdate = true;

        Object(float x, float y, float width, float height);
        Object(const Rect &rect);

        const Vertex *getVertices() const;

        size_t getSize() const;

        void setTexture(const Rect &rect);
    };

}