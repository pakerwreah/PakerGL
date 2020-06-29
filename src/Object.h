#pragma once

#include "Vertex.h"
#include <cstddef>

namespace PakerGL {

    class Object {
      private:
        Vertex vertexData[6];

      public:
        bool needsUpdate = true;

        Object(float x, float y, float width, float height);

        const Vertex *getVertices() const;

        size_t getSize() const;
    };

}