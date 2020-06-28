#pragma once

#include "Buffer.h"
#include "Vertex.h"

namespace PakerGL {

    class VertexBuffer : private Buffer {
      private:
        void initialize();

      public:
        VertexBuffer(size_t size);
        VertexBuffer(const Vertex *data, size_t size);
        virtual ~VertexBuffer() = default;

        using Buffer::bind;
        using Buffer::unbind;

        using Buffer::getSize;

        void setData(const Vertex *data, size_t offset, size_t size);
    };

}