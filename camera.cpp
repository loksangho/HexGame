#include"camera.h"
#include "keyreceiver.h"
#include <QGuiApplication>

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    Position = position;
/*#elif defined(Q_OS_WIN)
    Position = GLM_D3DX_Helper::ConvertVec3(position);
#endif*/
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    // Initializes matrices since otherwise they will be the null matrix


    this->FOVdeg = FOVdeg;

//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    // Makes camera look in the right direction from the right position
    view = glm::lookAt(Position, Position + Orientation, Up);

    // Adds perspective to the scene
    projection = glm::perspective(FOVdeg,(float)width/height, nearPlane, farPlane);

    // Sets new camera matrix
//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    cameraMatrix = projection * view;
//#elif defined(Q_OS_WIN)
//    cameraMatrix = projection * view;
//#endif;
/*#elif defined(Q_OS_WIN)
    D3DXMatrixIdentity(&view);
    D3DXMatrixIdentity(&projection);
    // Makes camera look in the right direction from the right position
    D3DXVECTOR3 At = Position + Orientation;
    D3DXMatrixLookAtLH(&view, &Position, &At, &Up);

    float aspect = (float) width/height;
    D3DXMatrixPerspectiveFovLH(&projection, D3DXToRadian(FOVdeg), aspect, nearPlane, farPlane);
    //view = glm::lookAt(Position, Position + Orientation, Up);
    //D3DXMATRIX transposed_proj;
    //D3DXMATRIX transposed_view;
    //D3DXMatrixTranspose(&transposed_proj, &projection);
    //D3DXMatrixTranspose(&transposed_view, &view);
    cameraMatrix = view * projection;


    // Adds perspective to the scene
    //projection = glm::perspectiveZO(FOVdeg,(float)width/height, nearPlane, farPlane);
    //projection = glm::translate(glm::vec3(0.0f,0.0f,0.5f)) * glm::scale(glm::vec3(1.0f,1.0f,0.5f)) * projection; // fix when translating from opengl to directx
    // Sets new camera matrix
    //cameraMatrix = glm::transpose(projection) * glm::transpose(view);*/
//#endif
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
#ifdef Q_OS_WIN

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


 /*   //This might have to go to constructor
    D3D11_BUFFER_DESC cbufDesc;
    ZeroMemory(&cbufDesc, sizeof(cbufDesc));
    cbufDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbufDesc.ByteWidth = sizeof(CamMatrixBufferType);
    cbufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbufDesc.MiscFlags = 0;
    cbufDesc.StructureByteStride = 0;

    CamMatrixBufferType camBuf;
    camBuf.camMatrix = cameraMatrix;

    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = &camBuf;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    HRESULT hr = shader->m_device->CreateBuffer(&cbufDesc, &InitData, &m_matrixBuffer);
    if (FAILED(hr))
        qFatal("Failed to create constant buffer: 0x%x", hr);
    shader->m_context->UpdateSubresource(m_matrixBuffer, 0 , 0, &camBuf, 0, 0);

    unsigned int bufferNumber;

    bufferNumber = 0;

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
//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
            Position += (1.f * speed) * -glm::normalize(glm::cross(Orientation, Up));
/*#elif defined(Q_OS_WIN)
            D3DXVECTOR3 cross_result;
            D3DXVec3Cross(&cross_result, &Orientation, &Up);
            D3DXVECTOR3 normalize_result;
            D3DXVec3Normalize(&normalize_result, &cross_result);
            Position += (1.f * speed) * -normalize_result;
#endif*/
        }

        if(press_key_s == 1) {
            Position += speed * -Orientation;
        }

        if(press_key_d == 1) {
//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
            Position += (1.f * speed) * glm::normalize(glm::cross(Orientation, Up));
/*#elif defined(Q_OS_WIN)
            D3DXVECTOR3 cross_result;
            D3DXVec3Cross(&cross_result, &Orientation, &Up);
            D3DXVECTOR3 normalize_result;
            D3DXVec3Normalize(&normalize_result, &cross_result);
            Position += (1.f * speed) * normalize_result;
#endif*/
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
            //std::cout << width << "," << height << std::endl;
            //QCursor::setPos(width/2, height/2);
            QCursor::setPos(-screenPosX+(width / 2), -screenPosY+(height / 2));

            //QCursor::setPos(100,100);
            float rotX = sensitivity*(float)(mouseY*1.0 - (height / 2)) / height;
            float rotY = sensitivity*(float)(mouseX*1.0 - (width / 2)) / width;



//#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
            glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

            if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                Orientation = newOrientation;
            }

            // Rotates the Orientation left and right
            Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
/*#elif defined(Q_OS_WIN)
            D3DXVECTOR3 cross_result;
            D3DXVec3Cross(&cross_result, &Orientation, &Up);
            D3DXVECTOR3 normalize_result;
            D3DXVec3Normalize(&normalize_result, &cross_result);
            D3DXMATRIX rotate_mat;
            D3DXMatrixRotationAxis(&rotate_mat, &normalize_result, D3DXToRadian(-rotX));
            D3DXVECTOR3 newOrientation;
            D3DXVec3TransformCoord(&newOrientation,  &Orientation, &rotate_mat);
            // need a way to  find the angle between two vectors, D3DX does not provide such a function
            glm::vec3 newOrientationGLM = glm::vec3(newOrientation.x, newOrientation.y, newOrientation.z);
            glm::vec3 UpGLM = glm::vec3(Up.x, Up.y, Up.z);

            if (abs(glm::angle(newOrientationGLM, UpGLM) - D3DXToRadian(90.0f)) <= D3DXToRadian(85.0f))
            {
                Orientation = newOrientation;
            }
            D3DXMatrixRotationAxis(&rotate_mat, &Up, D3DXToRadian(-rotY));
            D3DXVec3TransformCoord(&Orientation,  &Orientation, &rotate_mat);

#endif*/
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

