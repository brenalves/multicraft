#pragma once

#include "buffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(VertexBuffer& vb, BufferLayout layout);

    void bind();
    void unbind();

private:
    unsigned int m_id;
};