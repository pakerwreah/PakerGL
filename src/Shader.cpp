#include "Shader.h"

#include <GL/glew.h>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PakerGL {

    static std::string readFile(const std::string &filepath) {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in) {
            in.seekg(0, std::ios::end);
            std::streamsize size = in.tellg();
            if (size != -1) {
                result.resize((size_t)size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
                in.close();
            } else {
                std::cerr << "Could not read from file " << filepath << std::endl;
            }
        } else {
            std::cerr << "Could not open from file " << filepath << std::endl;
        }

        return result;
    }

    Shader::Shader() {
        m_RendererID = glCreateProgram();
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    void Shader::bind() const {
        glUseProgram(m_RendererID);
    }

    void Shader::unbind() {
        glUseProgram(0);
    }

    void Shader::setProjection(int width, int height) const {
        int location = glGetUniformLocation(m_RendererID, "projection");
        glm::mat4 projection = glm::ortho(0.f, (float)width, (float)height, 0.f, -1.f, 1.f);
        glProgramUniformMatrix4fv(m_RendererID, location, 1, GL_FALSE, glm::value_ptr(projection));
    }

    void Shader::setColor(const std::string &name, const Color &color) const {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform4f(m_RendererID, location, color.red, color.green, color.blue, color.alpha);
    }

    void Shader::setTexture(const std::string &name, int unit) const {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform1i(m_RendererID, location, unit);
    }

    void Shader::compile(uint type, const std::string &filepath) {
        std::string source = readFile(filepath);

        uint shader = glCreateShader(type);

        const char *sourceCStr = source.c_str();
        glShaderSource(shader, 1, &sourceCStr, nullptr);

        glCompileShader(shader);

        int isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_TRUE) {
            shaders.push_back(shader);
        } else {
            int maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog((size_t)maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            std::cerr << "Shader compilation failure!" << std::endl
                      << infoLog.data() << std::endl;
        }
    }

    void Shader::link() {
        for (auto shader : shaders) {
            glAttachShader(m_RendererID, shader);
        }

        // Link our program
        glLinkProgram(m_RendererID);

        int isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            int maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<char> infoLog((size_t)maxLength);
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

            std::cerr << "Shader link failure!" << std::endl
                      << infoLog.data() << std::endl;
        }

        for (auto shader : shaders) {
            glDetachShader(m_RendererID, shader);
            glDeleteShader(shader);
        }
    }

}
