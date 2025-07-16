#include "ShaderProgram.h"
#include <iostream>

namespace Renderer
{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderID;
        GLuint fragmentShaderID;

        if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
        {
            std::cerr << "VERTEX SHADER compile error" << std::endl;
            return;
        }

        if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cerr << "FRAGMENT SHADER compile error" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        GLint success;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
            std::cerr << "Shader LINK error:\n" << infoLog << std::endl;
            return;
        }

        m_isCompiled = true;

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
    {
        m_ID = other.m_ID;
        m_isCompiled = other.m_isCompiled;

        other.m_ID = 0;
        other.m_isCompiled = false;
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteProgram(m_ID);

            m_ID = other.m_ID;
            m_isCompiled = other.m_isCompiled;

            other.m_ID = 0;
            other.m_isCompiled = false;
        }
        return *this;
    }

    bool ShaderProgram::createShader(const std::string& source, GLenum shaderType, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "Shader COMPILE error:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    bool ShaderProgram::isCompiled() const { return m_isCompiled; }

    void ShaderProgram::use() const
    {
        if (m_isCompiled)
            glUseProgram(m_ID);
    }
}
