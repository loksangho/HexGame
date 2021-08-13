#include "ebo.h"
#include <iostream>

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(std::vector<GLuint>& indices)
{
#ifdef Q_OS_MACX
    glGenBuffersARB(1, &ID);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

#elif defined(Q_OS_WIN)


//PFNGLGENBUFFERSARBPROC glGenBuffersARB;
//glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");

//PFNGLBINDBUFFERARBPROC glBindBufferARB;
//glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");

//PFNGLBUFFERDATAARBPROC glBufferDataARB;
//glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");

glGenBuffers(1, &ID);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

#elif defined(Q_OS_LINUX)
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
#endif
}

void EBO::Bind() {
#ifdef Q_OS_MACX
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, ID);

#elif defined(Q_OS_WIN)
    //PFNGLBINDBUFFERARBPROC glBindBufferARB;
    //glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
#elif defined(Q_OS_LINUX)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
#endif
}

void EBO::Unbind() {
#ifdef Q_OS_MACX
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#elif defined(Q_OS_WIN)
    //PFNGLBINDBUFFERARBPROC glBindBufferARB;
    //glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#elif defined(Q_OS_LINUX)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
}

void EBO::Delete() {
#ifdef Q_OS_MACX
    glDeleteBuffersARB(1, &ID);
#elif defined(Q_OS_WIN)
    //PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
    //glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");

    glDeleteBuffers(1, &ID);

#elif defined(Q_OS_LINUX)
    glDeleteBuffers(1, &ID);
#endif
}
