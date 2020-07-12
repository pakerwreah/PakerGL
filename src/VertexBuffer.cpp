#include "VertexBuffer.h"

#include <GL/glew.h>

namespace PakerGL {

    VertexBuffer::VertexBuffer(size_t size)
        : Buffer(size) {
        initialize();
    }

    VertexBuffer::VertexBuffer(const Vertex *data, size_t size)
        : Buffer(data, size) {
        initialize();
    }

    void VertexBuffer::initialize() {
        setAttribute(0, 2, sizeof(Vertex), offsetof(Vertex, origin));
        setAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, texture));
    }

    void VertexBuffer::setData(const Vertex *data, size_t offset, size_t size) {
        Buffer::setData(data, offset, size);
    }

}
