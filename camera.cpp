#include"camera.h"
#include "keyreceiver.h"
#include <QGuiApplication>

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    // Initializes matrices since otherwise they will be the null matrix
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    this->FOVdeg = FOVdeg;

    // Makes camera look in the right direction from the right position
    view = glm::lookAt(Position, Position + Orientation, Up);

    // Adds perspective to the scene
    projection = glm::perspective(glm::radians(FOVdeg),(float)width/height, nearPlane, farPlane);

    // Sets new camera matrix
    cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
#ifdef Q_OS_WIN
    //PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
    //glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) wglGetProcAddress("glGetUniformLocationARB");

    //PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB;
    //glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC) wglGetProcAddress("glUniformMatrix4fvARB");

    // Exports camera matrix
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
#elif defined(Q_OS_MAC) || defined (Q_OS_LINUX)
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
#endif



}

#ifdef Q_OS_WIN
void Camera::Init(D3D11Shader* shader) {
    /*D3D11_BUFFER_DESC matrixBufferDesc;
    ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
    matrixBufferDesc.StructureByteStride = 0;

    HRESULT hr = shader->m_device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
    if (FAILED(hr))
        qFatal("Failed to create matrix buffer: 0x%x", hr);
*/
}

void Camera::MatrixD3D11(D3D11Shader* shader) {

/*
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    //glm::mat4* dataPtr;
    unsigned int bufferNumber;
    glm::mat4 camMatrix = glm::transpose(cameraMatrix);
    HRESULT hr = shader->m_context->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(hr))
        qFatal("Failed to map matrix buffer: 0x%x", hr);


    memcpy(mappedResource.pData, &camMatrix, sizeof(glm::mat4));

    shader->m_context->Unmap(m_matrixBuffer, 0);

    bufferNumber = 5;

    shader->m_context->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

*/

}

void Camera::Delete() {
    if(m_matrixBuffer)
        m_matrixBuffer->Release();
}

#endif


void Camera::Inputs(int screenPosX, int screenPosY, int mouseX, int mouseY, int press_key_esc, int press_key_w, int press_key_a, int press_key_s, int press_key_d, int left_mouse_click)
{

    if(left_mouse_click==1) {

        if (firstClick)
        {
            QGuiApplication::setOverrideCursor(Qt::CrossCursor);
            //squircle->setCrossHair
           firstClick = false;
        }
    }
    if(press_key_esc==1) {
        firstClick = true;
    }
    if(!firstClick){
    // Handles key inputs
        if(press_key_w == 1) {
            Position += speed * Orientation;
        }

        if(press_key_a == 1) {
            Position += (1.f * speed) * -glm::normalize(glm::cross(Orientation, Up));
        }

        if(press_key_s == 1) {
            Position += speed * -Orientation;
        }

        if(press_key_d == 1) {
            Position += (1.f* speed) * glm::normalize(glm::cross(Orientation, Up));
        }

     /*   if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::Key_W))
        {
            Position += speed * Orientation;
        }
        if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::Key_A))
        {
            Position += speed * -glm::normalize(glm::cross(Orientation, Up));
        }
        if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::Key_S))
        {
            Position += speed * -Orientation;
        }
        if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::Key_D))
        {
            Position += speed * glm::normalize(glm::cross(Orientation, Up));
        }
        if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::Key_Space))
        {
            Position += speed * Up;
        }
        if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::Key_Control))
        {
            Position += speed * -Up;
        }
        if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::Key_Shift))
        {
            speed = 0.4f;
        }
        else
        {
            speed = 0.1f;
        }*/

        //std::cout << Position.x << "," << Position.y << "," << Position.z << std::endl;
        //Position += speed * -Orientation;
    /*
        // Handles mouse inputs
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            // Hides mouse cursor
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            // Prevents camera from jumping on the first click
            if (firstClick)
            {
                glfwSetCursorPos(window, (width / 2), (height / 2));
                firstClick = false;
            }
    */

            //QCursor::setPos(-screenPosX+(width / 2), -screenPosY+(height / 2));

            // Stores the coordinates of the cursor
            //double mouseX;
            //double mouseY;
            // Fetches the coordinates of the cursor
            //glfwGetCursorPos(window, &mouseX, &mouseY);

            //Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
            // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
            // and then "transforms" them into degrees
            //float rotX = sensitivity * (float)(mouseY*1.0 - (height / 2)) / height;
            //float rotY = sensitivity * (float)(mouseX*1.0 - (width / 2)) / width;

            //QCursor::setPos(-screenPosX+(width / 2), -screenPosY+(height / 2));
            float rotX = sensitivity*(float)(mouseY*1.0 - (height / 2)) / height;
            float rotY = sensitivity*(float)(mouseX*1.0 - (width / 2)) / width;

            //std::cout << std::max(width/2-abs(mouseX-width/2)/width,0) << std::endl;
            //std::cout << mouseX - wid << std::endl;

            //std::cout << mouseX << "," << mouseY << std::endl;
            // Calculates upcoming vertical change in the Orientation
            glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

            if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                Orientation = newOrientation;
            }

            // Rotates the Orientation left and right
            Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
        }

        else {
            QGuiApplication::setOverrideCursor(Qt::ArrowCursor);

        }

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
 /*       glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Makes sure the next time the camera looks around it doesn't jump
        firstClick = true;
    }
*/
}

