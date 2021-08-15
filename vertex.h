#ifndef VERTEX_H
#define VERTEX_H
#include "qglobal.h"
#include <glm/glm.hpp>


// Structure to standardize the vertices used in the meshes
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;

};

#if defined(Q_OS_WIN)
struct CamMatrixBufferType
{
    glm::mat4 camMatrix;
};
#endif

#endif // VERTEX_H
