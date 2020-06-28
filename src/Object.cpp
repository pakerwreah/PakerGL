#include "Object.h"

namespace PakerGL {

    Object::Object(float x, float y, float width, float height) {
        vertexData[0] = { x, y };
        vertexData[1] = { x + width, y };
        vertexData[2] = { x + width, y + height };
        vertexData[3] = { x, y + height };
    }

    const Vertex *Object::getVertices() const {
        return vertexData;
    }

    size_t Object::getSize() const {
        return sizeof(vertexData);
    }

}