#ifndef D3D11TEXTURE_H
#define D3D11TEXTURE_H

#include "d3d11shaderclass.h"

class D3D11Texture
{
#ifdef Q_OS_WIN

public:
   // GLuint ID;
    const char* type = nullptr;
    //GLuint unit;

    ID3D11SamplerState* ppSamplerState = 0;
    ID3D11ShaderResourceView* ppSRView = 0;

    D3D11Texture(D3D11Shader* shader, const char* image, const char* texType, unsigned int slot);
    ~D3D11Texture() {}

    // Assigns a texture unit to a texture
    void texUnit(D3D11Shader* shader, const char* uniform);
    // Binds a texture
    void Bind(D3D11Shader* shader);
    // Unbinds a texture
    void Unbind();
    // Deletes a texture
    void Delete();
#endif
};

#endif // D3D11TEXTURE_H
