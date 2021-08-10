#ifndef EBO_H
#define EBO_H

#ifdef Q_OS_WIN
    #include<QtGui/QOpenGLFunctions>
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include<QtGui/QOpenGLFunctions>
#endif

#define GL_GLEXT_PROTOTYPES
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
