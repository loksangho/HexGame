#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

/*
 *  This is the model class for both Direct3D 11 and OpenGL implementation of the 3D mode.
 *
 */

#include<json/json.hpp>
#include"mesh.h"
#include "d3d11mesh.h"

using json = nlohmann::json;


class Model
{
public:
    // Loads in a model from a file and stores tha information in 'data', 'JSON', and 'file'
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    Model(const char* file);
#endif

#ifdef Q_OS_WIN
    Model(D3D11Shader* shader, const char* file);

    void DrawD3D11(D3D11Shader* shader,Camera& camera, glm::mat4 matrices_mesh=glm::mat4(1.0f), bool pre=true);
    std::vector<D3D11Mesh> d3d11_meshes;
#endif
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    void Draw(Shader& shader,
              Camera& camera, glm::mat4 matrices_mesh=glm::mat4(1.0f), bool pre = true);
#endif
    // All the meshes and transformations
    std::vector<Mesh> meshes;
//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    std::vector<glm::vec3> translationsMeshes;
    std::vector<glm::quat> rotationsMeshes;
    std::vector<glm::vec3> scalesMeshes;
    std::vector<glm::mat4> matricesMeshes;
/*#elif defined(Q_OS_WIN)
    std::vector<D3DXVECTOR3> translationsMeshes;
    std::vector<D3DXQUATERNION> rotationsMeshes;
    std::vector<D3DXVECTOR3> scalesMeshes;
    std::vector<D3DXMATRIX> matricesMeshes;
#endif*/

private:
    // Variables for easy access
    const char* file;
    std::vector<unsigned char> data;
    json JSON;




    // Prevents textures from being loaded twice
    std::vector<std::string> loadedTexName;
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    std::vector<Texture> loadedTex;
#elif defined(Q_OS_WIN)
    std::vector<D3D11Texture> loadedTex;
#endif

};
#endif
