#include "model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>
#include <QFile>
#include <QtCore/QResource>

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
Model::Model(const char* file)
#elif defined(Q_OS_WIN)
Model::Model(D3D11Shader* shader, const char* file)
#endif

{
    // Make a JSON object
    std::string text = get_file_contents(file);

    //JSON = json::parse(text);

    // Get the binary data
    Model::file = file;

    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);


    Assimp::Importer importer;

    QFile file_q(file);
    if(!file_q.open(QFile::ReadOnly)) {
        std::cout << "Cannot read file" <<std::endl;
        return;
    }
    QByteArray file_bytes = file_q.readAll();
    file_q.close();
    // const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    const aiScene *scene = importer.ReadFileFromMemory(file_bytes.data(), file_bytes.size(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    // If the import failed, report it
    if( !scene) {
      std::cout << "import failed" << std::endl;
        return;
    }

    // Now we can access the file's contents.
    if(scene->HasMeshes()) {
        unsigned int total_num_of_meshes = scene->mNumMeshes;
        for(unsigned int i=0; i < total_num_of_meshes; i++) {

            aiMesh* mesh = scene->mMeshes[i];
            aiVector3D* normals = nullptr;

            aiVector3D* positions = nullptr;
            aiColor4D* colours = nullptr;
            aiVector3D* texCoords = nullptr;
            aiFace* faces = nullptr;

            if(mesh->HasNormals()) {
                normals = mesh->mNormals;
            }
            else {
                std::cout << "mesh has no normals" << std::endl;
            }

            if(mesh->HasPositions()) {
                positions = mesh->mVertices;
            }
            else {
                std::cout << "mesh has no positions" << std::endl;
            }

            if(mesh->HasTextureCoords(0)) {
                texCoords = mesh->mTextureCoords[0];

            }
            else {
                std::cout << "mesh has no texture coords" << std::endl;
            }

            if(mesh->HasVertexColors(0)) {
                colours = mesh->mColors[0];
            }

            if(mesh->HasFaces()) {
                faces = mesh->mFaces;

            }
            else {
                std::cout << "mesh has no faces" << std::endl;
            }

            //std::cout << std::string(mesh->mName.C_Str()).substr(0, std::string(mesh->mName.C_Str()).find("_")).c_str() << std::endl;
            aiNode* node = scene->mRootNode->FindNode(std::string(mesh->mName.C_Str()).substr(0, std::string(mesh->mName.C_Str()).find("_")).c_str()); // The name of the meshes must not have any periods (.) or underscores (_) in it, otherwise this will not work.
            aiMatrix4x4 globalMat;
            aiNode* current_node = node;
            int n=0;
            //std::cout << mesh->mName.C_Str() << std::endl;
            while(current_node != NULL) {
                //std::cout << n << std::endl;
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
                globalMat = current_node->mTransformation * globalMat;
#elif defined(Q_OS_WIN)
                globalMat = current_node->mTransformation * globalMat;
#endif
                current_node = current_node->mParent;
                n++;
            }
            //delete node;
            //delete current_node;
            glm::mat4 matrix_mesh(globalMat.a1,globalMat.b1,globalMat.c1,globalMat.d1,globalMat.a2,globalMat.b2,globalMat.c2,globalMat.d2,globalMat.a3,globalMat.b3,globalMat.c3,globalMat.d3,globalMat.a4,globalMat.b4,globalMat.c4,globalMat.d4);

            //for(int r=0; r<4; r++){
             //   for (int s=0; s< 4; s++){
             //       std::cout << matrix_mesh[r][s] << std::endl;
             //   }
            //
            //}


#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
            std::vector<Texture> textures;
#elif defined(Q_OS_WIN)
            std::vector<D3D11Texture> textures;
#endif


            assert(scene->HasMaterials());
            //if(scene->HasMaterials()) {
              aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                aiString* path_diff = new aiString();
                aiString* path_spec = new aiString();



                if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                    material->GetTexture(aiTextureType_DIFFUSE, 0, path_diff);
                }
                if(material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
                    material->GetTexture(aiTextureType_SPECULAR, 0, path_spec);
                }

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
                //Texture* diff_tex;
                //Texture* spec_tex;
#elif defined(Q_OS_WIN)

                //D3D11Texture* diff_tex = nullptr;
                //D3D11Texture* spec_tex = nullptr;
#endif
                std::string texPath_diff = std::string(path_diff->C_Str());
                std::string texPath_spec = std::string(path_diff->C_Str());

                // Check if the texture has already been loaded
                bool skip = false;
                for (unsigned int j = 0; j < loadedTexName.size(); j++)
                {
                    if (loadedTexName[j] == texPath_diff || loadedTexName[j] == texPath_spec)
                    {
                        textures.push_back(loadedTex[j]);
                        skip = true;
                        break;
                    }
                }

                // If the texture has been loaded, skip this
                if (!skip)
                {
                    if(path_diff->length != 0) {

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
                        Texture diff_tex((fileDirectory + path_diff->data).c_str(), "diffuse" ,loadedTex.size());
#elif defined(Q_OS_WIN)
                        D3D11Texture diff_tex(shader, (fileDirectory + path_diff->data).c_str(), "diffuse" ,loadedTex.size());

#endif
                        textures.push_back(diff_tex);
                        loadedTex.push_back(diff_tex);
                        loadedTexName.push_back(texPath_diff);



                    }
                    if(path_spec->length != 0) {
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
                        Texture spec_tex((fileDirectory + path_spec->data).c_str(), "specular" ,loadedTex.size());
#elif defined(Q_OS_WIN)
                        D3D11Texture spec_tex(shader, (fileDirectory + path_spec->data).c_str(), "specular" ,loadedTex.size());
#endif
                        textures.push_back(spec_tex);
                        loadedTex.push_back(spec_tex);
                        loadedTexName.push_back(texPath_spec);

                    }
                }

                delete path_diff;
                delete path_spec;

            //}


            std::vector<Vertex> vertices;

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
            std::vector<GLuint> indices;
#elif defined(Q_OS_WIN)
            std::vector<unsigned int> indices;
#endif

            assert(faces!=nullptr && positions!=nullptr && normals!=nullptr & texCoords!=nullptr);
            //if(faces!=nullptr && positions!=nullptr && normals!=nullptr & texCoords!=nullptr){
                //std::cout << mesh->mNumFaces << std::endl;

                //std::cout << "mesh numVertices: " << mesh->mNumVertices << std::endl;
                for(unsigned int j=0; j<mesh->mNumVertices; j++) {
                    //std::cout << positions[j].x << ", " << positions[j].y << ", " << positions[j].z << std::endl;
                    Vertex cur_vertex = Vertex {
//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)

                            glm::vec3((float)positions[j].x , (float)positions[j].y, (float)positions[j].z),
                            glm::vec3((float)normals[j].x, (float)normals[j].y, (float)normals[j].z),
                            colours!=nullptr?glm::vec3(colours[j].r, colours[j].g, colours[j].b):glm::vec3(1.0,1.0,1.0),
                            glm::vec2((float)texCoords[j].x, (float)texCoords[j].y)
/*#elif defined(Q_OS_WIN)
                            GLM_D3DX_Helper::ConvertVec3(glm::vec3((float)positions[j].x , (float)positions[j].y, (float)positions[j].z)),
                            GLM_D3DX_Helper::ConvertVec3(glm::vec3((float)normals[j].x, (float)normals[j].y, (float)normals[j].z)),
                            colours!=nullptr?GLM_D3DX_Helper::ConvertVec3(glm::vec3(colours[j].r, colours[j].g, colours[j].b)):D3DXVECTOR3(1.0,1.0,1.0),
                            GLM_D3DX_Helper::ConvertVec2(glm::vec2((float)texCoords[j].x, (float)texCoords[j].y))

#endif*/
                        };


                    vertices.push_back(cur_vertex);

                }
                //delete positions;
                //delete colours;
                //delete texCoords;
                //delete normals;

                //std::cout << "mesh->mNumFaces" << mesh->mNumFaces << std::endl;

                for(unsigned int m=0; m< mesh->mNumFaces; m++){
                    for(unsigned int k=0; k < faces->mNumIndices;k++){
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)

                        GLuint index = faces[m].mIndices[k];
                        //std::cout << faces[m].mIndices[k] << " ";
                        indices.push_back((GLuint)index);
#elif defined(Q_OS_WIN)
                        unsigned int index = faces[m].mIndices[k];
                        //std::cout << faces[m].mIndices[k] << " ";
                        indices.push_back((unsigned int)index);
#endif
                    }
                    //std::cout << ":" << m << std::endl;
                }

                //delete faces;

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
                Mesh cur_mesh(vertices, indices, textures);
#elif defined(Q_OS_WIN)
                D3D11Mesh cur_d3d11_mesh(shader, vertices, indices, textures);
#endif


                glm::mat4 matNextNode = matrix_mesh;// * glm::mat4(1.0f) * glm::mat4(1.0f) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0,1.0,1.0));
                //glm::mat4 matNextNode (1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0);
//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
                matricesMeshes.push_back(matNextNode);
                translationsMeshes.push_back(glm::vec3(0.0,0.0,0.0));
                rotationsMeshes.push_back(glm::quat(1.0,0.0,0.0,0.0));
                scalesMeshes.push_back(glm::vec3(1.0,1.0,1.0));
/*#elif defined(Q_OS_WIN)
                matricesMeshes.push_back(GLM_D3DX_Helper::ConvertMatrix(matNextNode));
                translationsMeshes.push_back(GLM_D3DX_Helper::ConvertVec3(glm::vec3(0.0,0.0,0.0)));
                rotationsMeshes.push_back(D3DXQUATERNION(0.0,0.0,0.0,1.0));
                scalesMeshes.push_back(GLM_D3DX_Helper::ConvertVec3(glm::vec3(1.0,1.0,1.0)));
#endif*/

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
                meshes.push_back(cur_mesh);
#elif defined(Q_OS_WIN)
                d3d11_meshes.push_back(cur_d3d11_mesh);
#endif


            //}



        }

    }


    // Traverse all nodes
    //traverseNode(0);

}

#if defined(Q_OS_WIN)
void Model::DrawD3D11(D3D11Shader* shader,Camera& camera, glm::mat4 matrices_mesh, bool pre)
{
    // Go over all meshes and draw each one
    for (unsigned long i = 0; i < d3d11_meshes.size(); i++)
    {
        if(pre) {
            d3d11_meshes[i].D3D11Mesh::Draw(shader, camera, matrices_mesh*matricesMeshes[i]);
        }
        else {
            d3d11_meshes[i].D3D11Mesh::Draw(shader, camera, matricesMeshes[i]*matrices_mesh);
        }
    }

/*    std::vector<Vertex> vertices;

    std::vector<unsigned int> indices;
    //For some reason it doesn't draw the last mesh, so I do it manually
    int lastIndex = d3d11_meshes.size()-1;
    for(unsigned long j=0; j < d3d11_meshes[lastIndex].vertices.size(); j++ ) {
        glm::vec3 position = d3d11_meshes[lastIndex].vertices[j].position;
        glm::vec3 normals = d3d11_meshes[lastIndex].vertices[j].normal;
        glm::vec3 colour = d3d11_meshes[lastIndex].vertices[j].color;
        glm::vec2 texCoord = d3d11_meshes[lastIndex].vertices[j].texUV;
        Vertex v = Vertex{position, normals,colour, texCoord};
        vertices.push_back(v);
    }
    for (unsigned long k=0; k < d3d11_meshes[lastIndex].indices.size(); k++) {
        indices.push_back(d3d11_meshes[lastIndex].indices[k]);
    }
    D3D11Mesh last_mesh(shader, vertices,indices, d3d11_meshes[lastIndex].textures);
    last_mesh.Draw(shader, camera, matricesMeshes[lastIndex]*matrices_mesh);
*/

}
#endif
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
void Model::Draw(Shader& shader,Camera& camera, glm::mat4 matrices_mesh)
{

    // Go over all meshes and draw each one
    for (unsigned long i = 0; i < meshes.size(); i++)
    {             
        meshes[i].Mesh::Draw(shader, camera, matricesMeshes[i]*matrices_mesh);

    }
#if defined(Q_OS_MACX) || defined(Q_OS_UNIX)
    std::vector<Vertex> vertices;

    std::vector<GLuint> indices;
    //For some reason it doesn't draw the last mesh, so I do it manually
    int lastIndex = meshes.size()-1;
    for(unsigned long j=0; j < meshes[lastIndex].vertices.size(); j++ ) {
        glm::vec3 position = meshes[lastIndex].vertices[j].position;
        glm::vec3 normals = meshes[lastIndex].vertices[j].normal;
        glm::vec3 colour = meshes[lastIndex].vertices[j].color;
        glm::vec2 texCoord = meshes[lastIndex].vertices[j].texUV;
        Vertex v = Vertex{position, normals,colour, texCoord};
        vertices.push_back(v);
    }
    for (unsigned long k=0; k < meshes[lastIndex].indices.size(); k++) {
        indices.push_back(meshes[lastIndex].indices[k]);
    }
    Mesh last_mesh(vertices,indices, meshes[lastIndex].textures);
    last_mesh.Draw(shader, camera, matricesMeshes[lastIndex]*matrices_mesh);
#endif
}
#endif

