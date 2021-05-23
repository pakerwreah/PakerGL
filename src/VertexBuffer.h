#pragma once

#include "Buffer.h"
#include "Vertex.h"

namespace PakerGL {

    class VertexBuffer : private Buffer {
      private:
        static void initialize();

      public:
        explicit VertexBuffer(size_t size);
        VertexBuffer(const Vertex *data, size_t size);
        ~VertexBuffer() override = default;

        using Buffer::bind;
        using Buffer::unbind;

        using Buffer::getSize;
        using Buffer::setData;
    };

}
