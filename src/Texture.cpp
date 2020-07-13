#include "Texture.h"

#include <GL/glew.h>
#include <stb_image.h>

namespace PakerGL {

    TextureMap::TextureMap(const std::unordered_map<std::string, std::string> &paths) {
        glGenTextures(1, &textureID);

        struct TexturePixels {
            std::string key;
            Texture texture;
            stbi_uc *pixels;
        };

        TexturePixels pixel_buffer[paths.size()];

        int total_width = 0, total_height = 0;
        {
            uint i = 0;
            for (auto &key_path : paths) {
                auto key = key_path.first;
                auto path = key_path.second;
                Texture texture;
                stbi_uc *pixels = stbi_load(path.c_str(), &texture.width, &texture.height, nullptr, STBI_rgb_alpha);
                assert(pixels != NULL);
                TexturePixels texturePixels { key, texture, pixels };
                total_height = std::max(texture.height, total_height);
                total_width += texture.width;
                pixel_buffer[i++] = texturePixels;
            }
        }

        int total_size = total_width * total_height * STBI_rgb_alpha;
        stbi_uc map_buffer[total_size];
        memset(map_buffer, 0, total_size);

        // COMBINE IMAGES
        int offset = 0;
        for (int i = 0; i < total_height; i++) {
            int line_offset = offset;
            for (auto &texturePixels : pixel_buffer) {
                Texture texture = texturePixels.texture;
                size_t size = texture.width * STBI_rgb_alpha;
                if (i < texture.height) {
                    memcpy(&map_buffer[line_offset], texturePixels.pixels + i * size, size);
                }
                line_offset += size;
            }
            offset += total_width * STBI_rgb_alpha;
        }

        // MAP COORDINATES
        float x_offset = 0;
        for (auto &texturePixels : pixel_buffer) {
            Texture texture = texturePixels.texture;
            float width = texture.width / (float)total_width;
            float height = texture.height / (float)total_height;
            texture.mapCoord = { x_offset, 0, width, height };
            textureMap[texturePixels.key] = texture;
            x_offset += width;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, total_width, total_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, map_buffer);

        for (auto texturePixels : pixel_buffer) {
            stbi_image_free(texturePixels.pixels);
        }
    }

    TextureMap::~TextureMap() {
        glDeleteTextures(1, &textureID);
    }

    Texture TextureMap::operator[](const std::string &name) const {
        return textureMap.at(name);
    }

    void TextureMap::bind(int unit) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

}