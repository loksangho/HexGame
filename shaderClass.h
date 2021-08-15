#ifndef SHADERCLASS_H
#define SHADERCLASS_H
#define GL_GLEXT_PROTOTYPES

/*
 *  This is the shader class for OpenGL implementation of the 3D mode (Mac and Linux).
 *
 */

#include "qglobal.h"

#ifdef Q_OS_WIN
    #include<QtGui/QOpenGLFunctions>
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include<QtGui/QOpenGLFunctions>
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QtQuick/QQuickItem>
#include <QOpenGLShaderProgram>


#include <QtQuick/qquickwindow.h>

std::string get_file_contents(const char* filename);

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();

private:
    void compileErrors(unsigned int shader, const char* type);
};

#endif // SHADERCLASS_H
