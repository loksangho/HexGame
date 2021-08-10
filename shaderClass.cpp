#include "shaderClass.h"
#include <QOpenGLShaderProgram>

#include <QtCore/QRunnable>
#include <QOpenGLBuffer>
#include <QFile>

std::string get_file_contents(const char* filename) {


    QFile File(filename);
    if(!File.open(QFile::ReadOnly)) {
        std::cout << "Cannot read file" <<std::endl;
        return "";
    }

    QByteArray content = File.readAll();

    File.close();

    //std::string final = QString(content).toStdString();


    return content.toStdString();

}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    // Read vertexFile and fragmentFile and store the strings
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    // Convert the shader source strings into character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get its reference

#ifdef Q_OS_WIN
    PFNGLCREATESHADERPROC glCreateShader;
    glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");

    PFNGLSHADERSOURCEPROC glShaderSource;
    glShaderSource = (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");

    PFNGLCOMPILESHADERPROC glCompileShader;
    glCompileShader = (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");

    PFNGLCREATEPROGRAMPROC glCreateProgram;
    glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");

    PFNGLATTACHSHADERPROC glAttachShader;
    glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");

    PFNGLLINKPROGRAMPROC glLinkProgram;
    glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");

    PFNGLDELETESHADERPROC glDeleteShader;
    glDeleteShader = (PFNGLDELETESHADERPROC) wglGetProcAddress("glDeleteShader");

#endif

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);
    // Checks if Shader compiled succesfully
    compileErrors(vertexShader, "VERTEX");

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);
    // Checks if Shader compiled succesfully
    compileErrors(fragmentShader, "FRAGMENT");

    // Create Shader Program Object and get its reference
    ID = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(ID);
    // Checks if Shaders linked succesfully
    compileErrors(ID, "PROGRAM");

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate()
{
#ifdef Q_OS_WIN
    PFNGLUSEPROGRAMPROC glUseProgram;
    glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
#endif
    glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
#ifdef Q_OS_WIN
    PFNGLDELETEPROGRAMPROC glDeleteProgram;
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC) wglGetProcAddress("glDeleteProgram");
#endif
    glDeleteProgram(ID);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{

#ifdef Q_OS_WIN
    PFNGLGETSHADERIVPROC glGetShaderiv;
    glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");

    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");

    PFNGLGETPROGRAMIVPROC glGetProgramiv;
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress("glGetProgramiv");

    PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress("glGetProgramInfoLog");
#endif
    // Stores status of compilation
    GLint hasCompiled;
    // Character array to store error message in
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
}
