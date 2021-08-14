#ifndef D3D11MESH_H
#define D3D11MESH_H

#include <vector>
#include "vertex.h"
#include "d3d11texture.h"
#include "camera.h"
#include <glm/glm.hpp>

class D3D11Mesh
{
public:
#ifdef Q_OS_WIN
    std::vector <Vertex> vertices;
    std::vector <unsigned int> indices;
    std::vector <D3D11Texture> textures;
    // Store VAO in public so it can be used in the Draw function

    ID3D11Buffer* m_cbuf = 0;
    ID3D11Buffer* m_vbuf = 0; //vertex
    ID3D11Buffer* m_indbuf = 0; //index
    ID3D11InputLayout *m_inputLayout = 0;

    // Initializes the mesh
    D3D11Mesh(D3D11Shader* shader, std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, std::vector <D3D11Texture>& textures);

    ~D3D11Mesh(){}

    void Delete();
    // Draws the mesh
    void Draw
    (
        D3D11Shader* shader,
        Camera& camera,
        glm::mat4 matrix = glm::mat4(1.0f),
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)

    );
    //void Draw(Shader& shader, Camera& camera);
#endif
};

#endif // D3D11MESH_H
