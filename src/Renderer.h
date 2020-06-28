#pragma once

#include "Object.h"
#include "VertexBuffer.h"
#include <memory>
#include <set>

namespace PakerGL {

    class Renderer {
      private:
        size_t dataSize = 0;
        std::set<std::shared_ptr<Object>> objects;
        std::unique_ptr<VertexBuffer> buffer;

      public:
        Renderer();

        void add(std::shared_ptr<Object> object);

        void remove(std::shared_ptr<Object> object);

        void render();
    };

}