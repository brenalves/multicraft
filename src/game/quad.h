#pragma once

#include "components/transform.h"
#include "components/mesh.h"
#include "components/material.h"
#include "core/resourcemanager.h"

class Quad
{
public:
    Quad();
    ~Quad();

    void update(float deltaTime);

    inline Transform& getTransform() { return m_transform; }
    inline Mesh& getMesh() { return *m_mesh; }
    inline Material& getMaterial() { return *m_material; }

private:
    Transform m_transform;
    Mesh* m_mesh;
    Material* m_material;
};