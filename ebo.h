#ifndef EBO_H
#define EBO_H

/*
 *  This is the OpenGL index buffer implementation class.
 *
 */

#include "qglobal.h"
#define GL_GLEXT_PROTOTYPES
#ifdef Q_OS_WIN
    #include <QOpenGLFunctions>
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include <QtGui/QOpenGLFunctions>
#endif


#include <QOpenGLShaderProgram>

class EBO
{
public:
    GLuint ID;
    EBO(std::vector<GLuint>& indices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif // EBO_H
