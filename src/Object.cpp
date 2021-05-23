#include "Object.h"

namespace PakerGL {

    Object::Object(float x, float y, float width, float height)
        : Object(Rect { x, y, width, height }) {
    }

    Object::Object(const Rect &rect) : m_rect(rect) {
        Object::resize(rect);
    }

    void Object::resize(const Rect &rect) {
        m_rect = rect;

        // Triangle 1
        vertexData[0].origin = rect.origin();
        vertexData[1].origin = { rect.end().x, rect.y };
        vertexData[2].origin = { rect.x, rect.end().y };

        // Triangle 2
        vertexData[3].origin = { rect.end().x, rect.y };
        vertexData[4].origin = { rect.x, rect.end().y };
        vertexData[5].origin = rect.end();

        needsUpdate = true;
    }

    const Vertex *Object::getVertices() const {
        return vertexData;
    }

    size_t Object::getSize() const {
        return sizeof(vertexData);
    }

    void Object::setTexture(const Texture &texture, bool keepAspect) {

        if (keepAspect) {
            float texRatio = (float)texture.width / (float)texture.height;
            float objRatio = m_rect.width / m_rect.height;

            if (texRatio > objRatio) {
                m_rect.height = m_rect.width / texRatio;
            } else {
                m_rect.width = m_rect.height * texRatio;
            }

            resize(m_rect);
        }

        auto rect = texture.mapCoord;

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
