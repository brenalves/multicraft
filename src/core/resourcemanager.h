#pragma once

#include <string>
#include <unordered_map>

#include "rendering/shader.h"
#include "rendering/texture.h"

class ResourceManager
{
public:
    static void initialize();
    static void shutdown();

    static Shader& loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
    static Shader& getShader(const std::string &name);

    static Texture& loadTexture(const std::string &name, const std::string &filePath);
    static Texture& getTexture(const std::string &name);

private:
    static std::unordered_map<std::string, Shader*> s_shaders;
    static std::unordered_map<std::string, Texture*> s_textures;
};