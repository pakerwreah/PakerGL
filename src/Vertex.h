#pragma once

#include "Types.h"

namespace PakerGL {

    struct Vertex {
        [[maybe_unused]] Point origin { 0, 0 };
        [[maybe_unused]] Point texture { -1, -1 };
    };

}
