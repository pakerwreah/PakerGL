#include "Object.h"
#include <stb_image.h>

namespace PakerGL {

    Object::Object(float x, float y, float width, float height)
        : Object(std::move(Rect { x, y, width, height })) {
    }

    Object::Object(const Rect &rect) {
        // Triangle 1
        vertexData[0].origin = rect.origin();
        vertexData[1].origin = { rect.end().x, rect.y };
        vertexData[2].origin = { rect.x, rect.end().y };

        // Triangle 2
        vertexData[3].origin = { rect.end().x, rect.y };
        vertexData[4].origin = { rect.x, rect.end().y };
        vertexData[5].origin = rect.end();
    }

    const Vertex *Object::getVertices() const {
        return vertexData;
    }

    size_t Object::getSize() const {
        return sizeof(vertexData);
    }

    void Object::setTexture(const Rect &rect) {
        // Triangle 1
        vertexData[0].texture = rect.origin();
        vertexData[1].texture = { rect.end().x, rect.y };
        vertexData[2].texture = { rect.x, rect.end().y };

        // Triangle 2
        vertexData[3].texture = { rect.end().x, rect.y };
        vertexData[4].texture = { rect.x, rect.end().y };
        vertexData[5].texture = rect.end();
    }
}