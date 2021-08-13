#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

// Structure to standardize the vertices used in the meshes
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
    //Vec3 position;
    //Vec3 normal;
    //Vec2 texUV:
};

struct MatrixBufferType
{
    glm::mat4 camMatrix;
};

struct Vec3 {
    glm::vec3 v;

};

struct VSConstantBuffer
{
     glm::mat4 camMatrix;
     glm::mat4 translation;
     glm::mat4 rotation;
     glm::mat4 scale;
     glm::mat4 model;
};

#endif // VERTEX_H
