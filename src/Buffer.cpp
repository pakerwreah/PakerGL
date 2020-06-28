#include "Buffer.h"
#include <GL/glew.h>

namespace PakerGL {

    Buffer::Buffer(size_t size) {
        this->size = size;
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    Buffer::Buffer(const void *data, size_t size) {
        this->size = size;
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    Buffer::~Buffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void Buffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void Buffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    size_t Buffer::getSize() {
        return size;
    }

    void Buffer::setData(const void *data, size_t offset, size_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void Buffer::setAttribute(uint index, uint count, size_t size, size_t offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, size, reinterpret_cast<void *>(offset));
    }

}
