#ifndef VERTEX_H
#define VERTEX_H
#include "qglobal.h"
#include <glm/glm.hpp>

/*
 *  This is a class with useful struct definitions for the 3D mode.
 *
 */

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
