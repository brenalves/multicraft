#pragma once

#include "rendering/shader.h"
#include "rendering/texture.h"

class Material
{
public:
    Material(Shader& shader);

    inline void setDiffuseMap(Texture* diffuse) { m_diffuseMap = diffuse; }
    inline void setSpecularMap(Texture* specular) { m_specularMap = specular; }

    inline Shader& getShader() { return m_shader; }
    inline Texture* getDiffuseMap() { return m_diffuseMap; }
    inline Texture* getSpecularMap() { return m_specularMap; }
    inline float getShininess() { return m_shininess; }

private:
    Shader& m_shader;
    Texture* m_diffuseMap;
    Texture* m_specularMap;
    float m_shininess;
};