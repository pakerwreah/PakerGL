#pragma once

#include <iostream>

namespace PakerGL {

    class Buffer {
      private:
        size_t size;

      protected:
        uint bufferID, vertexArrayID;

        void create(size_t size);

      public:
        Buffer(size_t maxSize);
        Buffer(const void *data, size_t size);
        virtual ~Buffer();

        void bind() const;
        void unbind() const;

        size_t getSize();

        void setData(const void *data, size_t offset, size_t size);
        void setAttribute(uint index, uint count, size_t size, size_t offset);
    };

}