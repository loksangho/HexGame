#include "mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    VAO1.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO(vertices);
    // Generates Element Buffer Object and links it to indices
    EBO EBO(indices);
    //EBO.Bind();
    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO1.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    VAO1.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));


    //for(Vertex v : vertices){
    //    std::cout << v.position.x << ", " << v.position.y << ", " << v.position.z << std::endl;
    //}
    //VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(8 * sizeof(float)));

    //for(GLuint i : indices) {
    //    std::cout << i << std::endl;
    //}

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void HandleGLError()
{
    GLenum error;
    int i = 0;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << i << " " << error << std::endl;
        i++;
    }
}
void Mesh::Draw
(
    Shader& shader,
    Camera& camera,
    glm::mat4 matrix,
    glm::vec3 translation,
    glm::quat rotation,
    glm::vec3 scale
)
{
    // Bind shader to be able to access uniforms
    shader.Activate();
    VAO1.Bind();

    // Keep track of how many of each type of textures we have
    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;
    for (unsigned int i = 0; i < textures.size(); i++)
    {

        std::string num;
        std::string type = textures[i].type;
        if (type == "diffuse")
        {
            //std::cout << "here1" << std::endl;
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }
    // Take care of the camera Matrix
#ifdef Q_OS_WIN
    //PFNGLUNIFORM3FARBPROC glUniform3fARB;
    //glUniform3fARB = (PFNGLUNIFORM3FARBPROC) wglGetProcAddress("glUniform3fARB");

    //PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    //glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
#elif defined(Q_OS_MACX)
    glUniform3fARB(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
#elif defined(Q_OS_LINUX)
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
#endif



    camera.Matrix(shader, "camMatrix");

    // Initialize matrices
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Transform the matrices to their correct form
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);


#ifdef Q_OS_WIN
    //PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
    //glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) wglGetProcAddress("glUniformMatrix4fv");

    //PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    //glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");


    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    glUniformMatrix4fvARB(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fvARB(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fvARB(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fvARB(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
#endif
    // Push the matrices to the vertex shader

    //std::cout << indices.size() << std::endl;
    //std::cout << vertices.size() << std::endl;
    // Draw the actual mesh
    //std::cout << "here2" << std::endl;
    //HandleGLError();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}


