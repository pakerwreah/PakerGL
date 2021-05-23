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
        m_vertices[0].origin = rect.origin();
        m_vertices[1].origin = { rect.end().x, rect.y };
        m_vertices[2].origin = { rect.x, rect.end().y };

        // Triangle 2
        m_vertices[3].origin = { rect.end().x, rect.y };
        m_vertices[4].origin = { rect.x, rect.end().y };
        m_vertices[5].origin = rect.end();

        needsUpdate = true;
    }

    void Object::moveTo(const Point &point) {
        Rect rect = m_rect;
        rect.x = point.x;
        rect.y = point.y;
        resize(rect);
    }

    void Object::moveBy(const Point &point) {
        moveTo(m_rect.origin() + point);
    }

    Object::Vertices Object::getVertices() const {
        return m_vertices;
    }

    Rect Object::getRect() const {
        return m_rect;
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
        m_vertices[0].texture = rect.origin();
        m_vertices[1].texture = { rect.end().x, rect.y };
        m_vertices[2].texture = { rect.x, rect.end().y };

        // Triangle 2
        m_vertices[3].texture = { rect.end().x, rect.y };
        m_vertices[4].texture = { rect.x, rect.end().y };
        m_vertices[5].texture = rect.end();
    }
}
