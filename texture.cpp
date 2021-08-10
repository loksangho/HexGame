#include"texture.h"

#include <QOpenGLTexture>

Texture::Texture(const char* image, const char* texType, GLuint slot)

{
    // Assigns the type of the texture ot the texture object
    type = texType;

    // Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips the image so it appears right side up
    //stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stores it in bytes
    QImage img(image);
    heightImg = img.height();
    widthImg = img.width();
    //std::cout << widthImg << ", " << heightImg << " " << image << std::endl;
    img = img.mirrored();
    if(img.isGrayscale()){
        img = img.convertToFormat(QImage::Format_Grayscale16);
        numColCh = 1;
    }
    else {
        if(img.hasAlphaChannel()){
            img = img.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
            numColCh = 4;
        }
        else {
            img = img.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
            //img.invertPixels();
            numColCh = 3;
        }
    }

    //std::cout << numColCh << std::endl;
    //img.invertPixels();
    //img = img.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
    unsigned char* bytes = img.bits();
    //unsigned char* bytes = stbi_load("/Users/loksangho/Desktop/MAV/Qt/Hex/brick.png", &widthImg, &heightImg, &numColCh, 0);

    //QOpenGLTexture* texture = new QOpenGLTexture(QImage(image).mirrored());
    //texture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);

    //texture->bind();

    // Generates an OpenGL texture object
#ifdef Q_OS_WIN
    PFNGLACTIVETEXTUREPROC glActiveTexture;
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress("glActiveTexture");

    PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");



#endif



        glGenTextures(1, &ID);
        // Assigns the texture to a Texture Unit
        glActiveTexture(GL_TEXTURE0 + slot);
        unit = slot;
        glBindTexture(GL_TEXTURE_2D, ID);

        // Configures the type of algorithm that is used to make the image smaller or bigger
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
        // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

        // Check what type of color channels the texture has and load it accordingly
        if (numColCh == 4)
            glTexImage2D
            (
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                bytes
            );
        else if (numColCh == 3) {
            //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D
            (
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                bytes
            );
        }
        else if (numColCh == 1)
            glTexImage2D
            (
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                bytes
            );
        else
            throw std::invalid_argument("Automatic Texture type recognition failed");

    // Generates MipMaps
    glGenerateMipmap(GL_TEXTURE_2D);

    //stbi_image_free(bytes);
    // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
#ifdef Q_OS_WIN
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");

    PFNGLUNIFORM1IPROC glUniform1i;
    glUniform1i = (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");
#endif


    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
#ifdef Q_OS_WIN
    PFNGLACTIVETEXTUREPROC glActiveTexture;
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress("glActiveTexture");
#endif

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
