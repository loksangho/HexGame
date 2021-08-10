#include"vbo.h"
#include <iostream>
#include <vector>

VBO::VBO(std::vector<Vertex>& vertices)
{
#ifdef Q_OS_MACX
    glGenBuffersARB(1, &ID);
    glBindBufferARB(GL_ARRAY_BUFFER, ID);
   // std::cout << vertices.size() << " " << vertices.size() * sizeof(Vertex) << std::endl;
    glBufferDataARB(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

#elif defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    PFNGLGENBUFFERSPROC glGenBuffers;
    glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffers");

    PFNGLBINDBUFFERPROC glBindBuffer;
    glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBuffer");

    PFNGLBUFFERDATAPROC glBufferData;
    glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress("glBufferData");


    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
   // std::cout << vertices.size() << " " << vertices.size() * sizeof(Vertex) << std::endl;
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
#endif

}


// Binds the VBO
void VBO::Bind()
{
#ifdef Q_OS_MACX
    glBindBufferARB(GL_ARRAY_BUFFER, ID);

#elif defined(Q_OS_WIN)
    PFNGLBINDBUFFERPROC glBindBuffer;
    glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBuffer");


    glBindBuffer(GL_ARRAY_BUFFER, ID);
#elif defined(Q_OS_LINUX)
    glBindBuffer(GL_ARRAY_BUFFER, ID);
#endif
}

// Unbinds the VBO
void VBO::Unbind()
{
#ifdef Q_OS_MACX
    glBindBufferARB(GL_ARRAY_BUFFER, 0);

#elif defined(Q_OS_WIN)

    PFNGLBINDBUFFERPROC glBindBuffer;
    glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBuffer");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
#elif defined(Q_OS_LINUX)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
}

// Deletes the VBO
void VBO::Delete()
{
#ifdef Q_OS_MACX
    glDeleteBuffersARB(1, &ID);

#elif defined(Q_OS_WIN)
    PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress("glDeleteBuffers");

    glDeleteBuffers(1, &ID);

#elif defined(Q_OS_LINUX)
    glDeleteBuffers(1, &ID);

#endif
}
