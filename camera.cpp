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


    this->FOVdeg = FOVdeg;

    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    // Makes camera look in the right direction from the right position
    view = glm::lookAt(Position, Position + Orientation, Up);

    // Adds perspective to the scene
    projection = glm::perspective(FOVdeg,(float)width/height, nearPlane, farPlane);

    // Sets new camera matrix
    cameraMatrix = projection * view;

}

void Camera::Matrix(Shader& shader, const char* uniform)
{
#ifdef Q_OS_WIN

#elif defined(Q_OS_MAC) || defined (Q_OS_LINUX)
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
#endif

}

#ifdef Q_OS_WIN

void Camera::Delete() {
    if(m_matrixBuffer)
        m_matrixBuffer->Release();
}

#endif

Camera::~Camera() {

}

// Runs at every pass. When player clicks on the 3D window, the variable 'firstClick' is activated the tracks cursor movement. When Escape key is pressed, it exists the mode.
// This is required as the cursor is locked in the middle of the window when in play.
void Camera::Inputs(int screenPosX, int screenPosY, int mouseX, int mouseY, int press_key_esc, int press_key_w, int press_key_a, int press_key_s, int press_key_d, int left_mouse_click)
{
    if(left_mouse_click==1) {

        if (firstClick)
        {

           QGuiApplication::setOverrideCursor(Qt::BlankCursor);

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
            Position += (1.f * speed) * glm::normalize(glm::cross(Orientation, Up));

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
#if defined(Q_OS_WIN) || defined(Q_OS_MAC)
        if(mouseX < width/2-5 || mouseX > width/2 +5 ) {
            QCursor::setPos(-screenPosX+(width / 2), -screenPosY + mouseY);
        }
        if(mouseY < height/2-5 || mouseY > height/2+5) {
           QCursor::setPos(-screenPosX + mouseX, -screenPosY+(height / 2));
        }
            //QCursor::setPos(-screenPosX+(width / 2), -screenPosY+(height / 2));
#endif

            float rotX = sensitivity*(float)(mouseY*1.0 - (height / 2)) / height;
            float rotY = sensitivity*(float)(mouseX*1.0 - (width / 2)) / width;



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

}

