#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>

namespace PakerGL {

    static uint32_t ShaderTypeFromString(const std::string &type) {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

		std::cerr << "Unknown shader type!" << std::endl;
        return 0;
    }

    Shader::Shader(const std::string &filepath) {
        std::string source = readFile(filepath);
        auto shaderSources = preProcess(source);
        compile(shaderSources);

        // Extract name from filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    Shader::Shader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
        : m_Name(name) {
        std::unordered_map<uint32_t, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(sources);
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    std::string Shader::readFile(const std::string &filepath) {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in) {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1) {
                result.resize(size);
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

    std::unordered_map<uint32_t, std::string> Shader::preProcess(const std::string &source) {
        std::unordered_map<uint32_t, std::string> shaderSources;

        const char *typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
        while (pos != std::string::npos) {
            size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
            assert(eol != std::string::npos); // Syntax error
            size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
            std::string type = source.substr(begin, eol - begin);
            assert(ShaderTypeFromString(type)); // Invalid shader type specified"

            size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
            assert(nextLinePos != std::string::npos);// Syntax error
            pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

            shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void Shader::compile(const std::unordered_map<uint32_t, std::string> &shaderSources) {
        GLuint program = glCreateProgram();
        assert(shaderSources.size() <= 2); // We only support 2 shaders for now
        std::array<uint32_t, 2> glShaderIDs;
        int glShaderIDIndex = 0;
        for (auto &kv : shaderSources) {
            uint32_t type = kv.first;
            const std::string &source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar *sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

				std::cerr << infoLog.data() << std::endl;
				std::cerr << "Shader compilation failure!" << std::endl;
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

        m_RendererID = program;

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);

            for (auto id : glShaderIDs)
                glDeleteShader(id);

            std::cerr << infoLog.data() << std::endl;
            std::cerr << "Shader link failure!" << std::endl;
            return;
        }

        for (auto id : glShaderIDs) {
            glDetachShader(program, id);
            glDeleteShader(id);
        }
    }

    void Shader::bind() const {
        glUseProgram(m_RendererID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    void Shader::setInt(const std::string &name, int value) {
        UploadUniformInt(name, value);
    }

    void Shader::setIntArray(const std::string &name, int *values, uint32_t count) {
        UploadUniformIntArray(name, values, count);
    }

    void Shader::setFloat(const std::string &name, float value) {
        UploadUniformFloat(name, value);
    }

    void Shader::UploadUniformInt(const std::string &name, int value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void Shader::UploadUniformIntArray(const std::string &name, int *values, uint32_t count) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, count, values);
    }

    void Shader::UploadUniformFloat(const std::string &name, float value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }
}