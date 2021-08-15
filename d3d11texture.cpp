#include "d3d11texture.h"
#ifdef Q_OS_WIN

D3D11Texture::D3D11Texture(D3D11Shader* shader, const char* image, const char* texType, unsigned int slot)

{
   type = texType;

    unsigned int rowPitch;
    QImage img(image);
    int heightImg = img.height();
    int widthImg = img.width();
    img = img.mirrored();
    img = img.convertToFormat(QImage::Format_RGBA8888_Premultiplied);

    D3D11_TEXTURE2D_DESC tDesc;
    ZeroMemory(&tDesc, sizeof(tDesc));
    tDesc.Width = widthImg;
    tDesc.Height = heightImg;
    tDesc.MipLevels = tDesc.ArraySize = 1;
    tDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    tDesc.SampleDesc.Count = 1;
    tDesc.Usage = D3D11_USAGE_DEFAULT;
    tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    tDesc.CPUAccessFlags = 0;
    tDesc.MiscFlags = 0;

    rowPitch = img.bytesPerLine();

    // To get the texture working, texture2D, shader resource view and sampler state are required

    // Generates the texture2D file
    ID3D11Texture2D* pTexture;
    HRESULT hr = shader->m_device->CreateTexture2D( &tDesc, NULL, &pTexture );
    if (FAILED(hr))
        qFatal("Failed to create texture 2D: 0x%x", hr);

    shader->m_context->UpdateSubresource(pTexture, 0, nullptr, img.bits(), rowPitch, 0);

    // Shader Resource View initialisation
    D3D11_SHADER_RESOURCE_VIEW_DESC pDesc;
    ZeroMemory(&pDesc, sizeof(pDesc));
    pDesc.Format = tDesc.Format; // same as tDesc
    pDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    pDesc.Texture2D.MostDetailedMip = 0;
    pDesc.Texture2D.MipLevels = -1;
    hr = shader->m_device->CreateShaderResourceView(pTexture, &pDesc, &ppSRView);
    if (FAILED(hr))
        qFatal("Failed to create shader resource view: 0x%x", hr);

    shader->m_context->GenerateMips(ppSRView);

    // Sampler initialisation
    D3D11_SAMPLER_DESC pSamplerDesc;
    ZeroMemory(&pSamplerDesc, sizeof(pSamplerDesc));
    pSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    pSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    pSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    pSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    pSamplerDesc.MipLODBias = 0.0f;
    pSamplerDesc.MaxAnisotropy = 1;
    pSamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    pSamplerDesc.BorderColor[0] = 0;
    pSamplerDesc.BorderColor[1] = 0;
    pSamplerDesc.BorderColor[2] = 0;
    pSamplerDesc.BorderColor[3] = 0;
    pSamplerDesc.MinLOD = 0;
    pSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = shader->m_device->CreateSamplerState(&pSamplerDesc, &ppSamplerState);
    if (FAILED(hr))
        qFatal("Failed to create sampler state: 0x%x", hr);


}

void D3D11Texture::Bind(D3D11Shader* shader)
{
    shader->m_context->PSSetShaderResources(0,1,&ppSRView);
    shader->m_context->PSSetSamplers(0,1,&ppSamplerState);
}

void D3D11Texture::Unbind()
{

}

void D3D11Texture::Delete()
{
    if(ppSamplerState)
        ppSamplerState->Release();

    if(ppSRView)
        ppSRView->Release();
}
#endif
