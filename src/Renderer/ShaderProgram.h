#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;

        ~ShaderProgram();

        bool isCompiled() const;
        void use() const;

    private:
        bool createShader(const std::string& source, GLenum shaderType, GLuint& shaderID);

    private:
        bool m_isCompiled = false;
        GLuint m_ID = 0;
    };
}
