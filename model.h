#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

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

    void DrawD3D11(D3D11Shader* shader,Camera& camera, glm::mat4 matrices_mesh=glm::mat4(1.0f));
    std::vector<D3D11Mesh> d3d11_meshes;
#endif

    void Draw(Shader& shader,
              Camera& camera, glm::mat4 matrices_mesh=glm::mat4(1.0f));
    // All the meshes and transformations
    std::vector<Mesh> meshes;
    std::vector<glm::vec3> translationsMeshes;
    std::vector<glm::quat> rotationsMeshes;
    std::vector<glm::vec3> scalesMeshes;
    std::vector<glm::mat4> matricesMeshes;

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


    /*
    // Loads a single mesh by its index
    void loadMesh(unsigned int indMesh);

    // Traverses a node recursively, so it essentially traverses all connected nodes
    void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

    // Gets the binary data from a file
    std::vector<unsigned char> getData();
    // Interprets the binary data into floats, indices, and textures
    std::vector<float> getFloats(json accessor);
    std::vector<GLuint> getIndices(json accessor);
    std::vector<Texture> getTextures();

    // Assembles all the floats into vertices
    std::vector<Vertex> assembleVertices
    (
        std::vector<glm::vec3> positions,
        std::vector<glm::vec3> normals,
        std::vector<glm::vec2> texUVs
    );

    // Helps with the assembly from above by grouping floats
    std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
    std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
    std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
    */
};
#endif
