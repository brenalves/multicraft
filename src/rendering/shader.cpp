#include "shader.h"

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    unsigned int vertexShader = createAndCompileShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = createAndCompileShader(fragmentPath, GL_FRAGMENT_SHADER);

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);

    int success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        char log[512];
        glGetProgramInfoLog(m_id, 512, nullptr, log);
        throw std::runtime_error("Shader linking error:\n" + std::string(log));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::bind()
{
    glUseProgram(m_id);
}

void Shader::unbind()
{
    glUseProgram(0);
}

unsigned int Shader::createAndCompileShader(const std::string &path, GLenum type)
{
    std::fstream shaderFile(path);
    if(!shaderFile.is_open())
        throw std::runtime_error("Invalid shader path: " + path);

    std::stringstream shaderSS;
    shaderSS << shaderFile.rdbuf();
    shaderFile.close();
    std::string shaderStr = shaderSS.str();
    const char* shaderSource = shaderStr.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        throw std::runtime_error("Shader compilation error: " + path + "\n" + std::string(log));
    }

    return shader;
}

int Shader::getUniformLocation(const std::string &name)
{
    if(m_uniformLocations.find(name) == m_uniformLocations.end())
    {
        m_uniformLocations[name] = glGetUniformLocation(m_id, name.c_str());
    }

    return m_uniformLocations[name];
}
