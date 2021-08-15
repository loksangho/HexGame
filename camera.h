#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

/*
 *  This class provides camera movement in the 3D mode.
 *
 */


#include "qglobal.h"


#define GL_GLEXT_PROTOTYPES

#ifdef Q_OS_WIN
    #include<QtGui/QOpenGLFunctions>
    #include <d3d11.h>
    #include <d3dcompiler.h>
    #include "d3d11shaderclass.h"
    #include "vertex.h"
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include<QtGui/QOpenGLFunctions>
#endif



#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "shaderClass.h"

class Camera
{
public:
    // Stores the main vectors of the camera
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);
    glm::mat4 view;
    glm::mat4 projection;

    float FOVdeg = 45.0f;

    // Prevents the camera from jumping around when first clicking left click
    bool firstClick = true;

    // Stores the width and height of the window
    int width;
    int height;

    // Adjust the speed of the camera and it's sensitivity when looking around
    float speed = 0.7f;
    float sensitivity = 100.0f;


    // Camera constructor to set up initial values
    Camera(int width, int height, glm::vec3 position);

    // Updates the camera matrix to the Vertex Shader
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
    // Exports the camera matrix to a shader
    void Matrix(Shader& shader, const char* uniform);
#ifdef Q_OS_WIN
    ID3D11Buffer *m_matrixBuffer = 0; //matrix

    void Delete();
#endif
    // Handles camera inputs
    void Inputs(int screenPosX, int screenPosY, int mouseX, int mouseY, int press_key_esc, int press_key_w, int press_key_a, int press_key_s, int press_key_d, int left_mouse_click);
};

#endif
