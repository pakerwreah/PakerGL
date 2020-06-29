#pragma once

// avoid missing raise.c
#ifdef __linux__
#define __debugbreak() \
    __asm__("int $3"); \
    __asm__("nop")
#else
#include <cassert>
#define __debugbreak() assert(false)
#endif

namespace PakerGL {
    void checkErrors();
}