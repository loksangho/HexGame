#ifndef VBO_H
#define VBO_H
#define GL_GLEXT_PROTOTYPES
#include "qglobal.h"


#ifdef Q_OS_WIN
    #include<QtGui/QOpenGLFunctions>
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include<QtGui/QOpenGLFunctions>
#endif

#include <glm/glm.hpp>
#include <vector>
struct Vec2 {
    float  s;
    float t;
};

struct Vec3 {
    float x;
    float y;
    float z;
};


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


class VBO
{
public:
    GLuint ID;
    VBO(std::vector<Vertex>& vertices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif // VBO_H
