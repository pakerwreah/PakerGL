#include "Renderer.h"
#include <GL/glew.h>

namespace PakerGL {

    Renderer::Renderer() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void Renderer::add(std::shared_ptr<Object> object) {
        if (objects.insert(object).second) {
            dataSize += object->getVertices().size() * sizeof(Vertex);
        }
    }

    void Renderer::remove(std::shared_ptr<Object> object) {
        if (objects.erase(object)) {
            dataSize -= object->getVertices().size() * sizeof(Vertex);
        }
    }

    void Renderer::render() {
        bool bufferResized = !buffer || buffer->getSize() < dataSize;

        if (bufferResized) {
            buffer = std::make_unique<VertexBuffer>(dataSize);
        }

        size_t offset = 0;
        for (auto &obj : objects) {
            const auto &vertices = obj->getVertices();
            const size_t size = vertices.size() * sizeof(Vertex);
            if (bufferResized || obj->needsUpdate) {
                Buffer::setData(vertices.data(), offset, size);
                obj->needsUpdate = false;
            }
            offset += size;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(dataSize / sizeof(Vertex)));
    }

}
