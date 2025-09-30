#pragma once

#include <glad/glad.h>
#include <vector>

class Buffer
{
public:
    Buffer(GLenum type);
    ~Buffer();

    void setData(const void *data, unsigned int size);

    void bind();
    void unbind();

private:
    unsigned int m_id;
    GLenum m_type;
};

class VertexBuffer : public Buffer
{
public:
    VertexBuffer();
};

class IndexBuffer : public Buffer
{
public:
    IndexBuffer();

    void setData(const unsigned int *data, unsigned int size);

    inline unsigned int getCount() { return m_count; }

private:
    unsigned int m_count;
};

struct BufferElement
{
    int count;
    GLenum type;
    bool normalized;
    unsigned int typeSize;
};

class BufferLayout
{
public:
    BufferLayout()
        : m_stride(0)
    {
    }

    template <typename T>
    void push(int count, bool normalized);

    inline std::vector<BufferElement> &getElements() { return m_elements; }
    inline unsigned int getStride() { return m_stride; }

private:
    std::vector<BufferElement> m_elements;
    unsigned int m_stride;
};

template <typename T>
inline void BufferLayout::push(int count, bool normalized)
{
    static_assert(false);
}

template <>
inline void BufferLayout::push<float>(int count, bool normalized)
{
    m_elements.push_back({count, GL_FLOAT, normalized, sizeof(float)});
    m_stride += count * sizeof(float);
}
