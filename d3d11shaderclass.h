#ifndef D3D11SHADERCLASS_H
#define D3D11SHADERCLASS_H

/*
 *  This is the shader class for Direct3D 11 implementation of the 3D mode.
 *
 */


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QtQuick/QQuickItem>
#include <QtQuick/qquickwindow.h>
#ifdef Q_OS_WIN

#include <d3d11.h>
#include <d3dcompiler.h>
#endif

std::string get_file_contents(const char* filename);

class D3D11Shader {
#ifdef Q_OS_WIN

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
    ID3D11VertexShader *m_vs = nullptr;
    ID3D11PixelShader *m_ps = nullptr;
    ID3D11Device *m_device = nullptr;
    ID3D11DeviceContext *m_context = nullptr;
    ID3D11BlendState *m_blendState = nullptr;
    ID3D11RasterizerState *m_rastState = nullptr;
    ID3D11DepthStencilState *m_dsState = nullptr;

    D3D11Shader(const char* vertexFile, const char* fragmentFile, ID3D11Device *m_device, ID3D11DeviceContext *m_context);

    void compileShader();

    void Activate();
    void mainPass();
    void Delete();
#endif

};
#endif // D3D11SHADERCLASS_H
