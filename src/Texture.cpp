#include "Texture.h"

#include <GL/glew.h>
#include <stb_image.h>

namespace PakerGL {

    Texture::Texture(const std::unordered_map<std::string, std::string> &paths) {
        glGenTextures(1, &textureID);
        // TODO: create texture atlas
        auto texture = paths.begin();
        coord_map[texture->first] = { 0, 0, 1, 1 };
        loadFromFile(texture->second);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &textureID);
    }

    Rect Texture::getCoord(const std::string &name) const {
        return coord_map.at(name);
    }

    void Texture::loadFromFile(const std::string &path) {
        stbi_uc *pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);

        assert(pixels != NULL);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        stbi_image_free(pixels);
    }

    void Texture::bind(int unit) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

}