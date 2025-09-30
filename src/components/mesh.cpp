#include "mesh.h"

Mesh::Mesh(BufferLayout &layout)
{
    m_va.addBuffer(m_vb, layout);
}

Mesh::~Mesh()
{
}

void Mesh::setVertices(const void *vertices, unsigned int size)
{
    m_vb.setData(vertices, size);
}

void Mesh::setIndices(const unsigned int *indices, unsigned int size)
{
    m_ib.setData(indices, size);
}

void Mesh::bind()
{
    m_va.bind();
    m_vb.bind();
    m_ib.bind();
}

void Mesh::unbind()
{
    m_va.unbind();
    m_vb.unbind();
    m_ib.unbind();
}
