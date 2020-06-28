#pragma once

#include <string>
#include <unordered_map>

namespace PakerGL {

    struct Color {
        float red, green, blue, alpha;
    };

    class Shader {
      public:
        Shader(const std::string &filepath);
        Shader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
        virtual ~Shader();

        void bind() const;
        void unbind() const;

        void setColor(const std::string &name, Color color);

        const std::string &getName() const { return m_Name; }

      private:
        std::string readFile(const std::string &filepath);
        std::unordered_map<uint32_t, std::string> preProcess(const std::string &source);
        void compile(const std::unordered_map<uint32_t, std::string> &shaderSources);

      private:
        uint32_t m_RendererID;
        std::string m_Name;
    };

}