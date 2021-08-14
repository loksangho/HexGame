#include "d3d11shaderclass.h"


#include <QtCore/QRunnable>

#include <QFile>

#ifdef Q_OS_WIN

// Constructor that build the Shader Program from 2 different shaders
D3D11Shader::D3D11Shader(const char* vertexFile, const char* fragmentFile, ID3D11Device *m_device, ID3D11DeviceContext *m_context)
{
    // Read vertexFile and fragmentFile and store the strings
    //std::string vertexCode = get_file_contents(vertexFile);
   // std::string fragmentCode = get_file_contents(fragmentFile);

    // Convert the shader source strings into character arrays
    //const char* vertexSource = vertexCode.c_str();
    //const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get its reference



    this->m_device = m_device;
    this->m_context = m_context;

    QString vertex_filename;
    QString fragment_filename;

    vertex_filename = QLatin1String(vertexFile);

   fragment_filename = QLatin1String(fragmentFile);

    QFile f_v(vertex_filename);
    if (!f_v.open(QIODevice::ReadOnly))
        qFatal("Failed to read shader %s", qPrintable(vertex_filename));

    const QByteArray vertex_contents = f_v.readAll();

    m_vert = vertex_contents;
    Q_ASSERT(!m_vert.isEmpty());
    m_vertEntryPoint = QByteArrayLiteral("main");

    QFile f_f(fragment_filename);
    if (!f_f.open(QIODevice::ReadOnly))
        qFatal("Failed to read shader %s", qPrintable(fragment_filename));

    const QByteArray fragment_contents = f_f.readAll();


    m_frag = fragment_contents;
    Q_ASSERT(!m_frag.isEmpty());
    m_fragEntryPoint = QByteArrayLiteral("main");




}

void D3D11Shader::compileShader()
{
    const char *target;
    target = "vs_5_0"; // Vertex stage

    ID3DBlob *bytecode_vs = nullptr;
    ID3DBlob *errors = nullptr;
    HRESULT hr = D3DCompile(m_vert.constData(), m_vert.size(),nullptr, nullptr, nullptr,m_vertEntryPoint.constData(), target, 0, 0, &bytecode_vs, &errors);
    if (FAILED(hr) || !bytecode_vs) {
        qWarning("HLSL shader compilation failed: 0x%x", uint(hr));
        if (errors) {
            const QByteArray msg(static_cast<const char *>(errors->GetBufferPointer()),errors->GetBufferSize());
            errors->Release();
            qWarning("%s", msg.constData());
        }
        vs = QByteArray();
        return;
    }

    QByteArray result_vs;
    result_vs.resize(bytecode_vs->GetBufferSize());
    memcpy(result_vs.data(), bytecode_vs->GetBufferPointer(), result_vs.size());
    bytecode_vs->Release();

    vs = result_vs;

    target = "ps_5_0";
    ID3DBlob *bytecode_fs = nullptr;
    hr = D3DCompile(m_frag.constData(), m_frag.size(),nullptr, nullptr, nullptr,m_fragEntryPoint.constData(), target, 0, 0, &bytecode_fs, &errors);
    if (FAILED(hr) || !bytecode_fs) {
        qWarning("HLSL shader compilation failed: 0x%x", uint(hr));
        if (errors) {
            const QByteArray msg(static_cast<const char *>(errors->GetBufferPointer()),errors->GetBufferSize());
            errors->Release();
            qWarning("%s", msg.constData());
        }
        fs = QByteArray();
        return;
    }
    QByteArray result_fs;
    result_fs.resize(bytecode_fs->GetBufferSize());
    memcpy(result_fs.data(), bytecode_fs->GetBufferPointer(), result_fs.size());
    bytecode_fs->Release();

    fs = result_fs;

}

void D3D11Shader::mainPass() {
    m_context->VSSetShader(m_vs, nullptr, 0); // this needs to be run every pass, while createvertexshader only runs once
    m_context->PSSetShader(m_ps, nullptr, 0);
    float blendConstants[] = { 1, 1, 1, 1 };
    m_context->OMSetBlendState(m_blendState, blendConstants, 0xFFFFFFFF);

}

// Activates the Shader Program
void D3D11Shader::Activate()
{

    compileShader();

    HRESULT hr = m_device->CreateVertexShader(vs.constData(), vs.size(), nullptr, &m_vs);
    if (FAILED(hr))
        qFatal("Failed to create vertex shader: 0x%x", hr);

    hr = m_device->CreatePixelShader(fs.constData(), fs.size(), nullptr, &m_ps);
    if (FAILED(hr))
        qFatal("Failed to create pixel shader: 0x%x", hr);

    D3D11_BLEND_DESC blendDesc;
    memset(&blendDesc, 0, sizeof(blendDesc));
    blendDesc.IndependentBlendEnable = true;
    D3D11_RENDER_TARGET_BLEND_DESC blend;
    memset(&blend, 0, sizeof(blend));
    blend.BlendEnable = true;
    blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blend.DestBlend = D3D11_BLEND_ONE;
    blend.BlendOp = D3D11_BLEND_OP_ADD;
    blend.SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
    blend.DestBlendAlpha = D3D11_BLEND_ONE;
    blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    blendDesc.RenderTarget[0] = blend;
    hr = m_device->CreateBlendState(&blendDesc, &m_blendState);
    if (FAILED(hr))
        qFatal("Failed to create blend state: 0x%x", hr);



}

// Deletes the Shader Program
void D3D11Shader::Delete()
{

    if (m_vs)
        m_vs->Release();

    if (m_ps)
        m_ps->Release();

    if (m_blendState)
        m_blendState->Release();


}
#endif
