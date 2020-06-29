#include "Object.h"

namespace PakerGL {

    Object::Object(float x, float y, float width, float height) {
        // Triangle 1
        vertexData[0] = { x, y };
        vertexData[1] = { x + width, y };
        vertexData[2] = { x, y + height };

        // Triangle 2
        vertexData[3] = vertexData[1];
        vertexData[4] = vertexData[2];
        vertexData[5] = { x + width, y + height };
    }

    const Vertex *Object::getVertices() const {
        return vertexData;
    }

    size_t Object::getSize() const {
        return sizeof(vertexData);
    }

}