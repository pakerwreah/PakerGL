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
            dataSize += object->getSize();
        }
    }

    void Renderer::remove(std::shared_ptr<Object> object) {
        if (objects.erase(object)) {
            dataSize -= object->getSize();
        }
    }

    void Renderer::render() {
        bool bufferResized = !buffer || buffer->getSize() < dataSize;

        if (bufferResized) {
            buffer = std::make_unique<VertexBuffer>(dataSize);
        }

        size_t offset = 0;
        for (auto &obj : objects) {
            if (bufferResized || obj->needsUpdate) {
                buffer->setData(obj->getVertices(), offset, obj->getSize());
                obj->needsUpdate = false;
                offset += obj->getSize();
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_QUADS, 0, dataSize / sizeof(Vertex));
    }

}