#include "vao.h"
#include <iostream>
#include "qglobal.h"

#define GL_GLEXT_PROTOTYPES


VAO::VAO(){
#ifdef Q_OS_MACX
    glGenVertexArraysAPPLE(1, &ID);
#elif defined(Q_OS_WIN)
    glGenVertexArrays(1, &ID);
#elif defined(Q_OS_LINUX)
    glGenVertexArrays(1, &ID);
#endif
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.Bind();

    #ifdef Q_OS_MACX
        glVertexAttribPointerARB(layout,numComponents,type, GL_FALSE, stride, offset);

        glEnableVertexAttribArrayARB(layout);
    #elif defined(Q_OS_WIN)

    glVertexAttribPointer(layout,numComponents,type, GL_FALSE, stride, offset);

    glEnableVertexAttribArray(layout);
    #elif defined(Q_OS_LINUX)
        glVertexAttribPointer(layout,numComponents,type, GL_FALSE, stride, offset);

        glEnableVertexAttribArray(layout);
    #endif

    VBO.Unbind();
}
void VAO::Bind() {
#ifdef Q_OS_MACX
    glBindVertexArrayAPPLE(ID);
#elif defined(Q_OS_WIN)

    glBindVertexArray(ID);
#elif defined(Q_OS_LINUX)
    glBindVertexArray(ID);
#endif
}
void VAO::Unbind(){
#ifdef Q_OS_MACX
    glBindVertexArrayAPPLE(0);
#elif defined(Q_OS_WIN)

    glBindVertexArray(0);
#elif defined(Q_OS_LINUX)
    glBindVertexArray(0);
#endif

}
void VAO::Delete() {

#ifdef Q_OS_MACX
    glDeleteVertexArrays(1, &ID);
#elif defined(Q_OS_WIN)

    glDeleteVertexArrays(1, &ID);
#elif defined(Q_OS_LINUX)
    glDeleteVertexArrays(1, &ID);
#endif
}
