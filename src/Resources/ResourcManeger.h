#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer {
    class ShaderProgram;
    using SharedProgram = ShaderProgram;
}

class ResourceManager {
private:
    using ShaderProgramsMap = std::map<std::string, std::shared_ptr<Renderer::SharedProgram>>;
    ShaderProgramsMap m_shaderPrograms;
    std::string m_path;

    std::string getFileString(const std::string& relativeFilePath) const;

public:
    ResourceManager(const std::string& executablePath);
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager() = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ~ResourceManager() = default;

    std::shared_ptr<Renderer::SharedProgram> loadShaders(
        const std::string& shaderName,
        const std::string& vertexPath,
        const std::string& fragmentPath
    );
    
    std::shared_ptr<Renderer::SharedProgram> getShaderProgram(const std::string& shaderName);
};
