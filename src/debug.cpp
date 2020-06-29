#include "debug.h"
#include <GL/glew.h>
#include <iostream>

namespace PakerGL {

    void checkErrors() {
        GLenum code;
        while ((code = glGetError()) != GL_NO_ERROR) {
            std::cerr << "[" << code << "] ";
            switch (code) {
            case GL_INVALID_ENUM:
                std::cerr << "Invalid enum";
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "Invalid operation";
                break;

            default:
                std::cerr << glewGetErrorString(code);
                break;
            }
            std::cerr << std::endl;
            __debugbreak();
        }
    }

}