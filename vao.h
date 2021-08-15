#ifndef VAO_H
#define VAO_H
#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES

/*
 *  This is the vertex array class for the OpenGL implementation (Mac and Linux).
 *
 */

#include "qglobal.h"

#include "vbo.h"
class VAO
{
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VAO_H
