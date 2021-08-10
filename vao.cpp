#include "vao.h"
#include <iostream>
#include "qglobal.h"

VAO::VAO(){
#ifdef Q_OS_MACX
    glGenVertexArraysAPPLE(1, &ID);
#elif defined(Q_OS_WIN)

    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) wglGetProcAddress("glGenVertexArrays");


    glGenVertexArrays(1, &ID);
#elif defined(Q_OS_LINUX)
    glGenVertexArraysOES(1, &ID);
#endif
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.Bind();

    #ifdef Q_OS_MACX
        glVertexAttribPointerARB(layout,numComponents,type, GL_FALSE, stride, offset);

        glEnableVertexAttribArrayARB(layout);
    #elif defined(Q_OS_WIN)

    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) wglGetProcAddress("glVertexAttribPointer");

    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress("glEnableVertexAttribArray");


    glVertexAttribPointer(layout,numComponents,type, GL_FALSE, stride, offset);

    glEnableVertexAttribArray(layout);
    #elif defined(Q_OS_LINUX)
        glVertexAttribPointer(layout,numComponents,type, GL_FALSE, stride, offset);

        glEnableVertexAttribArray(layout);
    #endif
    //glVertexAttribPointerARB(layout,numComponents,type, GL_FALSE, stride, offset);

    //glEnableVertexAttribArrayARB(layout);
    VBO.Unbind();
}
void VAO::Bind() {
#ifdef Q_OS_MACX
    glBindVertexArrayAPPLE(ID);
#elif defined(Q_OS_WIN)
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) wglGetProcAddress("glBindVertexArray");

    glBindVertexArray(ID);
#elif defined(Q_OS_LINUX)
    glBindVertexArrayOES(ID);
#endif
}
void VAO::Unbind(){
#ifdef Q_OS_MACX
    glBindVertexArrayAPPLE(0);
#elif defined(Q_OS_WIN)
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) wglGetProcAddress("glBindVertexArray");

    glBindVertexArray(0);
#elif defined(Q_OS_LINUX)
    glBindVertexArrayOES(0);
#endif

}
void VAO::Delete() {

#ifdef Q_OS_MACX
    glDeleteVertexArrays(1, &ID);
#elif defined(Q_OS_WIN)
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) wglGetProcAddress("glDeleteVertexArrays");

    glDeleteVertexArrays(1, &ID);
#elif defined(Q_OS_LINUX)
    glDeleteVertexArraysOES(1, &ID);
#endif
}
