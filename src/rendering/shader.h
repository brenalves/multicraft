#pragma once

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdexcept>

class Shader
{
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    void bind();
    void unbind();

    inline void setUniform1i(const std::string &name, int value) { glUniform1i(getUniformLocation(name), value); }
    inline void setUniform1f(const std::string &name, float value) { glUniform1f(getUniformLocation(name), value); }
    inline void setUniformMat4(const std::string &name, const float *value) { glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value); }

private:
    unsigned int createAndCompileShader(const std::string &path, GLenum type);
    int getUniformLocation(const std::string &name);

private:
    unsigned int m_id;
    std::unordered_map<std::string, int> m_uniformLocations;
};