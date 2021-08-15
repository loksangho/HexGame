#include "d3d11mesh.h"
#ifdef Q_OS_WIN

D3D11Mesh::D3D11Mesh(D3D11Shader* shader, std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, std::vector <D3D11Texture>& textures)
{
/*
    vertices = std::vector<Vertex>();
    Vertex v1;
    v1.position = glm::vec3(-1,-1,0);
    v1.normal = glm::vec3(0,0,1);
    v1.color = glm::vec3(1,1,1);
    v1.texUV = glm::vec2(0,1);
    Vertex v2;
    v2.position = glm::vec3(1,-1,0);
    v2.normal = glm::vec3(0,0,1);
    v2.color = glm::vec3(1,1,1);
    v2.texUV = glm::vec2(1,1);
    Vertex v3;
    v3.position = glm::vec3(0,1,0);
    v3.normal = glm::vec3(0,0,1);
    v3.color = glm::vec3(1,1,1);
    v3.texUV = glm::vec2(0.5,0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    indices=std::vector<unsigned int>();
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(1);

    textures = std::vector <D3D11Texture>();
    textures.push_back(D3D11Texture(shader, ":/models/stone01.tga", "diffuse", 0));
*/


    D3D11Mesh::vertices = vertices;
    D3D11Mesh::indices = indices;
    D3D11Mesh::textures = textures;


    D3D11_BUFFER_DESC bufDesc;
    ZeroMemory(&bufDesc, sizeof(bufDesc));
    bufDesc.ByteWidth = vertices.size() * sizeof(Vertex);
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    HRESULT hr = shader->m_device->CreateBuffer(&bufDesc, nullptr, &m_vbuf);
    if (FAILED(hr))
        qFatal("Failed to create buffer: 0x%x", hr);

    shader->m_context->UpdateSubresource(m_vbuf, 0, nullptr, vertices.data(), 0, 0);

    D3D11_BUFFER_DESC indbufDesc;
    ZeroMemory(&indbufDesc,sizeof(indbufDesc));
    indbufDesc.ByteWidth = indices.size() * sizeof(unsigned int);
    indbufDesc.Usage = D3D11_USAGE_DEFAULT;
    indbufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indbufDesc.CPUAccessFlags  = 0;
    indbufDesc.MiscFlags       = 0;

    // Define the resource data.
    //D3D11_SUBRESOURCE_DATA InitData;
    //InitData.pSysMem = indices.data();
    //InitData.SysMemPitch = 0;
    //InitData.SysMemSlicePitch = 0;

    hr = shader->m_device->CreateBuffer(&indbufDesc, nullptr, &m_indbuf);
    if (FAILED(hr))
        qFatal("Failed to create index buffer: 0x%x", hr);

    shader->m_context->UpdateSubresource(m_indbuf, 0, nullptr, indices.data(), 0, 0);


    D3D11_INPUT_ELEMENT_DESC inputDesc[4];
    ZeroMemory(inputDesc, sizeof(inputDesc));
    inputDesc[0].SemanticName = "POSITION";
    inputDesc[0].SemanticIndex = 0;
    inputDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // vec3
    inputDesc[0].InputSlot = 0;
    inputDesc[0].AlignedByteOffset = 0;
    inputDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

    inputDesc[1].SemanticName = "NORMAL";
    inputDesc[1].SemanticIndex = 0;
    inputDesc[1].Format = DXGI_FORMAT_R32G32B32_FLOAT; // vec3
    inputDesc[1].InputSlot = 0;
    inputDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    inputDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

    inputDesc[2].SemanticName = "COLOR";
    inputDesc[2].SemanticIndex = 0;
    inputDesc[2].Format = DXGI_FORMAT_R32G32B32_FLOAT; // vec3
    inputDesc[2].InputSlot = 0;
    inputDesc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    inputDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

    inputDesc[3].SemanticName = "TEXCOORD";
    inputDesc[3].SemanticIndex = 0;
    inputDesc[3].Format = DXGI_FORMAT_R32G32_FLOAT; // vec2
    inputDesc[3].InputSlot = 0;
    inputDesc[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    inputDesc[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

    hr = shader->m_device->CreateInputLayout(inputDesc, 4, shader->vs.constData(), shader->vs.size(), &m_inputLayout);
    if (FAILED(hr))
        qFatal("Failed to create input layout: 0x%x", hr);

}


void D3D11Mesh::Delete() {
    if (m_vbuf)
        m_vbuf->Release();

    if (m_inputLayout)
        m_inputLayout->Release();

    if (m_indbuf)
        m_indbuf->Release();

    if (m_transbuf)
        m_transbuf->Release();

    if (m_rotbuf)
        m_rotbuf->Release();

    if (m_scabuf)
        m_scabuf->Release();

    if (m_modelbuf)
        m_modelbuf->Release();
}

void D3D11Mesh::Draw
(
    D3D11Shader* shader,
    Camera& camera,
    glm::mat4 matrix,
    glm::vec3 translation,
    glm::quat rotation,
    glm::vec3 scale
        ) {
    //shader->Activate();

    camera.MatrixD3D11(shader);

    const UINT stride = sizeof(Vertex); // vertex
    const UINT offset = 0;
    shader->m_context->IASetVertexBuffers(0, 1, &m_vbuf, &stride, &offset);
    const UINT ind_offset = 0;
    shader->m_context->IASetIndexBuffer(m_indbuf, DXGI_FORMAT_R32_UINT,ind_offset);
    shader->m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    shader->m_context->IASetInputLayout(m_inputLayout);


    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;
    for (unsigned int i = 0; i < textures.size(); i++)
    {

        std::string num;
        std::string type = textures[i].type;
        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        textures[i].Bind(shader);
    }

    // Initialize matrices
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Transform the matrices to their correct form
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

/*
    TranslationBuffer transBuffer;
    transBuffer.translation = glm::transpose(trans);

    RotationBuffer rotBuffer;
    rotBuffer.rotation = glm::transpose(rot);

    ScaleBuffer scaBuffer;
    scaBuffer.scale = glm::transpose(sca);
*/


    CamMatrixBufferType camMatrixBuffer;
    //D3DXMATRIX transposed_mvp;
    //D3DXMATRIX mvp = GLM_D3DX_Helper::ConvertMatrix(matrix * trans * rot * sca) * camera.cameraMatrix;
    //D3DXMatrixTranspose(&transposed_mvp, &mvp);
    camMatrixBuffer.camMatrix = glm::transpose(camera.cameraMatrix*sca*rot*trans*matrix) ;
    //


   /* //Do this for translation buffer
    D3D11_BUFFER_DESC cbufDesc;
    ZeroMemory(&cbufDesc, sizeof(cbufDesc));
    cbufDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbufDesc.ByteWidth = sizeof(TranslationBuffer);
    cbufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbufDesc.MiscFlags = 0;
    cbufDesc.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = &transBuffer;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    HRESULT hr = shader->m_device->CreateBuffer(&cbufDesc, &InitData, &m_transbuf);
    if (FAILED(hr))
        qFatal("Failed to create translation constant buffer: 0x%x", hr);

    shader->m_context->UpdateSubresource(m_transbuf, 0 , 0, &transBuffer, 0, 0);
    shader->m_context->VSSetConstantBuffers(1, 1, &m_transbuf); // first parameter is buffer number and it's 1

    //Do this for rotation buffer
    ZeroMemory(&cbufDesc, sizeof(cbufDesc));
    cbufDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbufDesc.ByteWidth = sizeof(RotationBuffer);
    cbufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbufDesc.MiscFlags = 0;
    cbufDesc.StructureByteStride = 0;
    InitData.pSysMem = &rotBuffer;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    hr = shader->m_device->CreateBuffer(&cbufDesc, &InitData, &m_rotbuf);
    if (FAILED(hr))
        qFatal("Failed to create rotation constant buffer: 0x%x", hr);

    shader->m_context->UpdateSubresource(m_rotbuf, 0 , 0, &rotBuffer, 0, 0);
    shader->m_context->VSSetConstantBuffers(2, 1, &m_rotbuf);


    //Do this for scale buffer
    ZeroMemory(&cbufDesc, sizeof(cbufDesc));
    cbufDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbufDesc.ByteWidth = sizeof(ScaleBuffer);
    cbufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbufDesc.MiscFlags = 0;
    cbufDesc.StructureByteStride = 0;
    InitData.pSysMem = &scaBuffer;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    hr = shader->m_device->CreateBuffer(&cbufDesc, &InitData, &m_scabuf);
    if (FAILED(hr))
        qFatal("Failed to create rotation constant buffer: 0x%x", hr);

    shader->m_context->UpdateSubresource(m_scabuf, 0 , 0, &scaBuffer, 0, 0);
    shader->m_context->VSSetConstantBuffers(3, 1, &m_scabuf);
*/
    //Do this for model buffer
    D3D11_BUFFER_DESC cbufDesc;
    ZeroMemory(&cbufDesc, sizeof(cbufDesc));
    cbufDesc.Usage = D3D11_USAGE_DEFAULT;
    cbufDesc.ByteWidth = sizeof(CamMatrixBufferType);
    cbufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    //cbufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    //cbufDesc.MiscFlags = 0;
    //cbufDesc.StructureByteStride = 0;



    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = &camMatrixBuffer;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    HRESULT hr = shader->m_device->CreateBuffer(&cbufDesc, &InitData, &m_modelbuf);
    if (FAILED(hr))
        qFatal("Failed to create cam matrix constant buffer: 0x%x", hr);

    shader->m_context->UpdateSubresource(m_modelbuf, 0, 0, &camMatrixBuffer, 0, 0);

    shader->m_context->VSSetConstantBuffers(0, 1, &m_modelbuf);


    shader->m_context->DrawIndexed(indices.size(),0,0);

}
#endif
