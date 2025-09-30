#include "material.h"

Material::Material(Shader &shader)
    : m_shader(shader)
{
    m_diffuseMap = nullptr;
    m_specularMap = nullptr;
    m_shininess = 32.0f;
}