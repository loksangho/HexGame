#ifndef D3D11SHADERCLASS_H
#define D3D11SHADERCLASS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QtQuick/QQuickItem>
#include <QtQuick/qquickwindow.h>
#include <d3d11.h>
#include <d3dcompiler.h>

std::string get_file_contents(const char* filename);

class D3D11Shader {
public:
    enum Stage {
        VertexStage,
        FragmentStage
    };
    QByteArray m_vert;
    QByteArray m_vertEntryPoint;
    QByteArray m_frag;
    QByteArray m_fragEntryPoint;
    QByteArray vs;
    QByteArray fs;
    ID3D11VertexShader *m_vs = 0;
    ID3D11PixelShader *m_ps = 0;
    ID3D11Device *m_device = nullptr;
    ID3D11DeviceContext *m_context = nullptr;
    ID3D11BlendState *m_blendState = 0;

    D3D11Shader(const char* vertexFile, const char* fragmentFile, ID3D11Device *m_device, ID3D11DeviceContext *m_context);

    void compileShader();

    void Activate();
    void mainPass();
    void Delete();

};
#endif // D3D11SHADERCLASS_H
