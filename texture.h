#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

/*
 *  This is the class handling the texture for the OpenGL implementation of the 3D mode (Mac and Linux)
 *
 */

#include "qglobal.h"

#define GL_GLEXT_PROTOTYPES
#ifdef Q_OS_WIN
    #include<QtGui/QOpenGLFunctions>
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include<QtGui/QOpenGLFunctions>
#endif

#include"shaderClass.h"

class Texture
{
public:
    GLuint ID;
    const char* type;
    GLuint unit;


    Texture(const char* image, const char* texType, GLuint slot);

    // Assigns a texture unit to a texture
    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    // Binds a texture
    void Bind();
    // Unbinds a texture
    void Unbind();
    // Deletes a texture
    void Delete();
};
#endif
