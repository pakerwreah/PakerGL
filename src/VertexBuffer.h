#pragma once

#include <iostream>

namespace PakerGL {

    class VertexBuffer {
      public:
        VertexBuffer(uint32_t size);
        VertexBuffer(const void *vertices, uint32_t size);
        virtual ~VertexBuffer();

        void bind() const;
        void unbind() const;

        void setData(const void *data, uint32_t size);

      private:
        uint32_t m_RendererID;
    };

    class IndexBuffer {
      public:
        IndexBuffer(uint32_t *indices, uint32_t count);
        virtual ~IndexBuffer();

        void bind() const;
        void unbind() const;

        uint32_t getCount() const {
            return count;
        }

      private:
        uint32_t m_RendererID;
        uint32_t count;
    };

}