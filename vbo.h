#ifndef VBO_H
#define VBO_H
#include "qglobal.h"
#define GL_GLEXT_PROTOTYPES


#ifdef Q_OS_WIN
    #include<QOpenGLFunctions>
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include<QtGui/QOpenGLFunctions>
#endif

#include <glm/glm.hpp>
#include <vector>
#include "vertex.h"




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
