#include "model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>
#include <QFile>
#include <QtCore/QResource>

Model::Model(const char* file)
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
    const aiScene *scene = importer.ReadFileFromMemory(file_bytes.data(), file_bytes.size(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_FindInvalidData | aiProcess_FindDegenerates);

    // If the import failed, report it
    if( !scene) {
      std::cout << "import failed" << std::endl;
        return;
    }

    // Now we can access the file's contents.
    if(scene->HasMeshes()) {
        //std::cout << scene->mNumMeshes << std::endl;

        for(int i=0; i< scene->mNumMeshes;i++) {
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
            //    std::cout << n << std::endl;
                globalMat = current_node->mTransformation * globalMat;
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

            std::vector<Texture> textures;
            if(scene->HasMaterials()) {
                aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                aiString* path_diff = new aiString();
                aiString* path_spec = new aiString();



                if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                    material->GetTexture(aiTextureType_DIFFUSE, 0, path_diff);
                }
                if(material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
                    material->GetTexture(aiTextureType_SPECULAR, 0, path_spec);
                }
                Texture* diff_tex;
                Texture* spec_tex;
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
                        diff_tex = new Texture((fileDirectory + path_diff->data).c_str(), "diffuse" ,loadedTex.size());
                        textures.push_back(*diff_tex);
                        loadedTex.push_back(*diff_tex);
                        loadedTexName.push_back(texPath_diff);
                        delete diff_tex;


                    }
                    if(path_spec->length != 0) {
                        spec_tex = new Texture((fileDirectory + path_spec->data).c_str(), "specular" ,loadedTex.size());
                        textures.push_back(*spec_tex);
                        loadedTex.push_back(*spec_tex);
                        loadedTexName.push_back(texPath_spec);
                        delete spec_tex;

                    }
                }
                delete path_diff;
                delete path_spec;

            }


            std::vector<Vertex> vertices;
            std::vector<GLuint> indices;
            if(faces!=nullptr && positions!=nullptr && normals!=nullptr & texCoords!=nullptr){
                //std::cout << mesh->mNumFaces << std::endl;

                //std::cout << "mesh numVertices: " << mesh->mNumVertices << std::endl;
                for(unsigned int j=0; j<mesh->mNumVertices; j++) {

                    Vertex cur_vertex = Vertex {
                            glm::vec3((float)positions[j].x , (float)positions[j].y, (float)positions[j].z),
                            glm::vec3((float)normals[j].x, (float)normals[j].y, (float)normals[j].z),
                            colours!=nullptr?glm::vec3(colours[j].r, colours[j].g, colours[j].b):glm::vec3(1.0,1.0,1.0),
                            glm::vec2((float)texCoords[j].x, (float)texCoords[j].y)
                        };


                    vertices.push_back(cur_vertex);

                }
                //delete positions;
                //delete colours;
                //delete texCoords;
                //delete normals;

                for(unsigned int m=0; m< mesh->mNumFaces; m++){
                    for(unsigned int k=0; k < faces->mNumIndices;k++){
                        GLuint index = faces[m].mIndices[k];
                        //std::cout << faces[m].mIndices[k] << std::endl;
                        indices.push_back((GLuint)index);
                    }
                }

                //delete faces;


                Mesh cur_mesh(vertices, indices, textures);

                glm::mat4 matNextNode = matrix_mesh;// * glm::mat4(1.0f) * glm::mat4(1.0f) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0,1.0,1.0));
                //glm::mat4 matNextNode (1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0);
                matricesMeshes.push_back(matNextNode);


                translationsMeshes.push_back(glm::vec3(0.0,0.0,0.0));
                rotationsMeshes.push_back(glm::quat(1.0,0.0,0.0,0.0));
                scalesMeshes.push_back(glm::vec3(1.0,1.0,1.0));
                meshes.push_back(cur_mesh);




            } //aiMesh* mesh = scene->mMeshes[i];



        }
    }

    // Traverse all nodes
    //traverseNode(0);

}



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

void Model::loadMesh(unsigned int indMesh)
{

    // Get all accessor indices
    unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
    unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
    unsigned int texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];

    // Use accessor indices to get all vertices components
    std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
    std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
    std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
    std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
    std::vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
    std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);

    // Combine all the vertex components and also get the indices and textures
    std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
    std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
    std::vector<Texture> textures = getTextures();

    // Combine the vertices, indices, and textures into a mesh
    meshes.push_back(Mesh(vertices, indices, textures));
}

void Model::traverseNode(unsigned int nextNode, glm::mat4 matrix)
{


    // Current node
    json node = JSON["nodes"][nextNode];


    // Get translation if it exists
    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
    if (node.find("translation") != node.end())
    {
        float transValues[3];
        for (unsigned int i = 0; i < node["translation"].size(); i++)
            transValues[i] = (node["translation"][i]);
        translation = glm::make_vec3(transValues);
    }
    // Get quaternion if it exists
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    if (node.find("rotation") != node.end())
    {
        float rotValues[4] =
        {
            node["rotation"][3],
            node["rotation"][0],
            node["rotation"][1],
            node["rotation"][2]
        };
        rotation = glm::make_quat(rotValues);
    }


    // Get scale if it exists
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    if (node.find("scale") != node.end())
    {
        float scaleValues[3];
        for (unsigned int i = 0; i < node["scale"].size(); i++)
            scaleValues[i] = (node["scale"][i]);
        scale = glm::make_vec3(scaleValues);
    }

    // Get matrix if it exists
    glm::mat4 matNode = glm::mat4(1.0f);
    if (node.find("matrix") != node.end())
    {
        float matValues[16];
        for (unsigned int i = 0; i < node["matrix"].size(); i++)
            matValues[i] = (node["matrix"][i]);
        matNode = glm::make_mat4(matValues);
    }

    // Initialize matrices
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Use translation, rotation, and scale to change the initialized matrices
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    // Multiply all matrices together
    glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

    // Check if the node contains a mesh and if it does load it
    if (node.find("mesh") != node.end())
    {
        translationsMeshes.push_back(translation);
        rotationsMeshes.push_back(rotation);
        scalesMeshes.push_back(scale);
        matricesMeshes.push_back(matNextNode);

        loadMesh(node["mesh"]);

    }

    // Check if the node has children, and if it does, apply this function to them with the matNextNode
    if (node.find("children") != node.end())
    {
        for (unsigned int i = 0; i < node["children"].size(); i++)
            traverseNode(node["children"][i], matNextNode);
    }
}

std::vector<unsigned char> Model::getData()
{
    // Create a place to store the raw text, and get the uri of the .bin file
    std::string bytesText;
    std::string uri = JSON["buffers"][0]["uri"];

    // Store raw text data into bytesText
    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

    bytesText = get_file_contents((fileDirectory + uri).c_str());

    // Transform the raw text data into bytes and put them in a vector
    std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
    return data;
}

std::vector<float> Model::getFloats(json accessor)
{
    std::vector<float> floatVec;


    // Get properties from the accessor
    unsigned int buffViewInd = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    // Get properties from the bufferView
    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    // Interpret the type and store it into numPerVert
    unsigned int numPerVert;
    if (type == "SCALAR") numPerVert = 1;
    else if (type == "VEC2") numPerVert = 2;
    else if (type == "VEC3") numPerVert = 3;
    else if (type == "VEC4") numPerVert = 4;
    //else if (type == "MAT2") numPerVert = 4;
    //else if (type == "MAT3") numPerVert = 9;
    //else if (type == "MAT4") numPerVert = 16;
    else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

    // Go over all the bytes in the data at the correct place using the properties from above
    unsigned int beginningOfData = byteOffset + accByteOffset;
    unsigned int lengthOfData = count * 4 * numPerVert;
    for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i)
    {

        unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };


        float value;
        std::memcpy(&value, bytes, sizeof(float));


        floatVec.push_back(value);
    }


    return floatVec;
}

std::vector<GLuint> Model::getIndices(json accessor)
{
    std::vector<GLuint> indices;

    // Get properties from the accessor
    unsigned int buffViewInd = accessor.value("bufferView", 0);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    unsigned int componentType = accessor["componentType"];

    // Get properties from the bufferView
    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    // Get indices with regards to their type: unsigned int, unsigned short, or short
    unsigned int beginningOfData = byteOffset + accByteOffset;
    if (componentType == 5125)
    {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
        {
            unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
            unsigned int value;
            std::memcpy(&value, bytes, sizeof(unsigned int));
            indices.push_back((GLuint)value);
        }
    }
    else if (componentType == 5123)
    {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
        {
            unsigned char bytes[] = { data[i++], data[i++] };
            unsigned short value;
            std::memcpy(&value, bytes, sizeof(unsigned short));
            indices.push_back((GLuint)value);
        }
    }
    else if (componentType == 5122)
    {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
        {
            unsigned char bytes[] = { data[i++], data[i++] };
            short value;
            std::memcpy(&value, bytes, sizeof(short));
            indices.push_back((GLuint)value);
        }
    }

    return indices;
}

std::vector<Texture> Model::getTextures()
{
    std::vector<Texture> textures;

    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

    // Go over all images
    for (unsigned int i = 0; i < JSON["images"].size(); i++)
    {
        // uri of current texture
        std::string texPath = JSON["images"][i]["uri"];

        // Check if the texture has already been loaded
        bool skip = false;
        for (unsigned int j = 0; j < loadedTexName.size(); j++)
        {
            if (loadedTexName[j] == texPath)
            {
                textures.push_back(loadedTex[j]);
                skip = true;
                break;
            }
        }

        // If the texture has been loaded, skip this
        if (!skip)
        {
            // Load diffuse texture
            if (texPath.find("baseColor") != std::string::npos)
            {
                Texture diffuse = Texture((fileDirectory + texPath).c_str(), "diffuse", loadedTex.size());
                textures.push_back(diffuse);
                loadedTex.push_back(diffuse);
                loadedTexName.push_back(texPath);
            }
            // Load specular texture
            else if (texPath.find("metallicRoughness") != std::string::npos)
            {
                Texture specular = Texture((fileDirectory + texPath).c_str(), "specular", loadedTex.size());
                textures.push_back(specular);
                loadedTex.push_back(specular);
                loadedTexName.push_back(texPath);
            }
        }
    }

    return textures;
}

std::vector<Vertex> Model::assembleVertices
(
    std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> texUVs
)
{
    std::vector<Vertex> vertices;
    for (int i = 0; i < positions.size(); i++)
    {
        //std::cout << positions[i].y << std::endl;
        vertices.push_back
        (
            Vertex
            {
                    positions[i],
                    normals[i],
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    texUVs[i]

            }
        );
    }
    return vertices;
}

std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floatVec)
{
    std::vector<glm::vec2> vectors;
    for (int i = 0; i < floatVec.size(); i)
    {
        vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
    }
    return vectors;
}
std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floatVec)
{
    std::vector<glm::vec3> vectors;
    for (int i = 0; i < floatVec.size(); i)
    {
        vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
    }
    return vectors;
}
std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floatVec)
{
    std::vector<glm::vec4> vectors;
    for (int i = 0; i < floatVec.size(); i)
    {
        vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
    }
    return vectors;
}
