#include "resourcemanager.h"

std::unordered_map<std::string, Shader*> ResourceManager::s_shaders;
std::unordered_map<std::string, Texture*> ResourceManager::s_textures;

void ResourceManager::initialize()
{
}

void ResourceManager::shutdown()
{
    for (auto& pair : s_shaders)
        delete pair.second;

    for (auto& pair : s_textures)
        delete pair.second;
}

Shader& ResourceManager::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath)
{
    if (s_shaders.find(name) != s_shaders.end())
        throw std::runtime_error("Shader with name '" + name + "' already exists");

    Shader* shader = new Shader(vertexPath, fragmentPath);
    s_shaders[name] = shader;
    return *shader;
}

Shader& ResourceManager::getShader(const std::string &name)
{
    if (s_shaders.find(name) == s_shaders.end())
        throw std::runtime_error("Shader with name '" + name + "' not found");

    return *s_shaders[name];
}

Texture& ResourceManager::loadTexture(const std::string &name, const std::string &filePath)
{
    if (s_textures.find(name) != s_textures.end())
        throw std::runtime_error("Texture with name '" + name + "' already exists");

    Texture* texture = new Texture(filePath);
    s_textures[name] = texture;
    return *texture;
}

Texture& ResourceManager::getTexture(const std::string &name)
{
    if (s_textures.find(name) == s_textures.end())
        throw std::runtime_error("Texture with name '" + name + "' not found");

    return *s_textures[name];
}
