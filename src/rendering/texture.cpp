#include "texture.h"

#include <iostream>

Texture::Texture(const std::string &path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);
    if (!data)
        throw std::runtime_error("Invalid texture path: " + path);

    glGenTextures(1, &m_id);

    setFilterMode(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    setWrapMode(GL_REPEAT, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::setFilterMode(GLenum min, GLenum mag)
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setWrapMode(GLenum s, GLenum t)
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
