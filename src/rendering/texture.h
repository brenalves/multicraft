#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string>
#include <stdexcept>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    void setFilterMode(GLenum min, GLenum mag);
    void setWrapMode(GLenum s, GLenum t);

    void bind(unsigned int slot = 0);
    void unbind();

private:
    unsigned int m_id;
    int m_width;
    int m_height;
    int m_channels;
};