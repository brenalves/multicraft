#include "buffer.h"

Buffer::Buffer(GLenum type)
    : m_type(type)
{
    glGenBuffers(1, &m_id);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_id);
}

void Buffer::setData(const void *data, unsigned int size)
{
    bind();
    glBufferData(m_type, size, data, GL_STATIC_DRAW);
    unbind();
}

void Buffer::bind()
{
    glBindBuffer(m_type, m_id);
}

void Buffer::unbind()
{
    glBindBuffer(m_type, 0);
}

VertexBuffer::VertexBuffer()
    : Buffer(GL_ARRAY_BUFFER)
{
}

IndexBuffer::IndexBuffer()
    : Buffer(GL_ELEMENT_ARRAY_BUFFER), m_count(0)
{
}

void IndexBuffer::setData(const unsigned int *data, unsigned int size)
{
    Buffer::setData(data, size);
    m_count = size / sizeof(unsigned int);
}
