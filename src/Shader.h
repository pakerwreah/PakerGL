#pragma once

#include <string>
#include <unordered_map>

namespace PakerGL {

    class Shader {
      public:
        Shader(const std::string &filepath);
        Shader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
        virtual ~Shader();

        virtual void bind() const;
        virtual void unbind() const;

        virtual void setInt(const std::string &name, int value);
        virtual void setIntArray(const std::string &name, int *values, uint32_t count);
        virtual void setFloat(const std::string &name, float value);

        virtual const std::string &getName() const { return m_Name; }

        void UploadUniformInt(const std::string &name, int value);
        void UploadUniformIntArray(const std::string &name, int *values, uint32_t count);
        void UploadUniformFloat(const std::string &name, float value);

      private:
        std::string readFile(const std::string &filepath);
        std::unordered_map<uint32_t, std::string> preProcess(const std::string &source);
        void compile(const std::unordered_map<uint32_t, std::string> &shaderSources);

      private:
        uint32_t m_RendererID;
        std::string m_Name;
    };

}