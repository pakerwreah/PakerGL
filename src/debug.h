#pragma once

#include <GL/glew.h>
#include <iostream>

inline void checkErrors() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "[" << err << "] ";
        switch (err) {
        case GL_INVALID_ENUM:
            std::cerr << "Invalid enum";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "Invalid operation";
            break;

        default:
            std::cerr << glewGetErrorString(err);
            break;
        }
        std::cerr << std::endl;
        assert(false);
    }
}