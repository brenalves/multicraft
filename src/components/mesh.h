#pragma once

#include "rendering/buffer.h"
#include "rendering/vertexarray.h"

class Mesh
{
public:
    Mesh(BufferLayout& layout);
    ~Mesh();

    void setVertices(const void* vertices, unsigned int size);
    void setIndices(const unsigned int* indices, unsigned int size);

    void bind();
    void unbind();

    inline VertexArray& getVA() { return m_va; }
    inline VertexBuffer& getVB() { return m_vb; }
    inline IndexBuffer& getIB() { return m_ib; }

private:
    VertexArray m_va;
    VertexBuffer m_vb;
    IndexBuffer m_ib;
};

// template <typename T>
// inline Mesh<T>::Mesh()
// {

// }

// template <typename T>
// inline Mesh<T>::~Mesh()
// {
// }

// template <typename T>
// inline void Mesh<T>::setVertices(const T *vertices, unsigned int count)
// {
// }

// template <typename T>
// inline void Mesh<T>::setIndices(const unsigned int *indices, unsigned int count)
// {
//     m_ib.setData(indices, count * sizeof(unsigned int));    
// }

// template <typename T>
// inline void Mesh<T>::bind()
// {
//     m_va.bind();
//     m_vb.bind();
//     m_ib.bind();
// }

// template <typename T>
// inline void Mesh<T>::unbind()
// {
//     m_va.unbind();
//     m_vb.unbind();
//     m_ib.unbind();
// }
