/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "squircle.h"


#include <QOpenGLShaderProgram>

#include <QtCore/QRunnable>
#include <QOpenGLBuffer>
#include "shaderClass.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "stb_image.h"
#include <QFile>
#include "texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "camera.h"
#include <QQuickRenderControl>
#include <QApplication>
#include <QSignalMapper>
#include "keyreceiver.h"
#include <QShortcut>
#include "mesh.h"
#include "model.h"
#include <vector>
#include <QString>
#include <QMessageBox>
#include <QTimer>



unsigned int width = 800;
unsigned int height = 800;


//! [7]
Squircle::Squircle()
    : m_t(0)
    , m_renderer(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &Squircle::handleWindowChanged);
    setFlag(QQuickItem::ItemHasContents, true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
    QCoreApplication::instance()->installEventFilter(this);
}
//! [7]

//! [8]
void Squircle::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}
//! [8]

void Squircle::init(int board_length, Colour player_colour, int difficulty) {

    this->board_length = board_length;
    this->player_colour = player_colour;
    aiplay = new AIPlay(this, player_colour, difficulty);
}


//! [1]
void Squircle::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &Squircle::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &Squircle::cleanup, Qt::DirectConnection);
//! [1]
//! [3]
        // Ensure we start with cleared to black. The squircle's blend mode relies on this.
        win->setColor(Qt::black);
    }

}
//! [3]



//! [6]
void Squircle::cleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
    delete aiplay;
}

class CleanupJob : public QRunnable
{
public:
    CleanupJob(SquircleRenderer *renderer) : m_renderer(renderer) { }
    void run() override { delete m_renderer; }
private:
    SquircleRenderer *m_renderer;
};

void Squircle::releaseResources()
{
    window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;

}

void Squircle::set_button_colour(int button_index, Colour c) {
    if(m_renderer) {
        m_renderer->set_button_colour(button_index, c);
    }
}

SquircleRenderer::SquircleRenderer(): m_t(0), m_program(0) {

    std::cout << "SquircleRenderer::init" << std::endl;
    model = new Model(":/models/cube_robot/robot.dae");
    model_table = new Model(":/models/table/table.dae");
    model_ball = new Model(":/models/sphere/sphere.dae");
    model_red_blocks = new Model(":/models/hexagon3D/red_blocks.dae");
    model_blue_blocks = new Model(":/models/hexagon3D/blue_blocks.dae");
}

AIPlay::AIPlay(Squircle* squircle, Colour player_colour, int difficulty)
{
    this->squircle = squircle;
    this->player_colour = player_colour;
    switch(difficulty){
    case 0:
        mc_trials = 50;
        break;
    case 1:
        mc_trials = 200;
        break;
    case 2:
        mc_trials = 1000;
        break;
    default:
        mc_trials= 50;
    }
    start_game();
    set_move();

}


void AIPlay::handleResults(const QString &str) {

    destroy_thread_manager();
    int move_int = str.toInt();
    QPair<int,int> move_pair = board->convert_index_to_location(move_int, board->get_length());
    if(board->is_legal(move_pair.first, move_pair.second, switch_turn(player_colour))) {
        board->make_move(move_pair.first, move_pair.second, switch_turn(player_colour));
        set_button_colour(board->convert_location_to_index(move_pair.first, move_pair.second), switch_turn(player_colour));
        turn = switch_turn(turn);
    }
    else {
        std::cout << "AI making illegal move. Should not be here" << std::endl;
    }
    Colour winner = board->has_winner(false);
    if(winner != Colour::EMPTY) {

        if(player_colour == winner) {
           QMessageBox msg_box(this);
           msg_box.setInformativeText("You Win!");
           msg_box.exec();
            std::cout << "You Win!" << std::endl;
            end_game();
        }
        else {
            QMessageBox msg_box(this);
            msg_box.setInformativeText("You Lose!");
            msg_box.exec();
            std::cout << "You Lose!" << std::endl;
            end_game();
        }
    }
    else {
        //std::cout << *board << std::endl;
        set_enable_buttons(true);
    }
}
void AIPlay::set_button_colour(int button_index, Colour c) {
    squircle->set_button_colour(button_index,c);
}


void AIPlay::set_enable_buttons(bool b) {

    squircle->set_enable_buttons(b);
}

// Passing on the method for enabling/disabling the buttons on the board
void Squircle::set_enable_buttons(bool b) {
    this->hex_buttons_enabled = b;
    if(m_renderer){
        m_renderer->set_enable_buttons(b);
    }

}

void SquircleRenderer::set_enable_buttons(bool b) {
    this->hex_buttons_enabled = b;
}

SquircleRenderer::~SquircleRenderer()
{
    //delete m_program;
    //delete m_window;
    for(int k=0; k< board_length*board_length; k++) {
        delete models_neutral_hexagon[k];
    }

    //remove the rigidbodies from the dynamics world and delete them
    for (int i=dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--) {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);

        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);

        delete obj;
    }

    for(int j=0; j< collisionShapes.size(); j++) {
        btCollisionShape* shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;

    }

    //delete dynamics world
    delete dynamicsWorld;

    //delete solver
    delete solver;

    //delete broadphase
    delete overlappingPairCache;

    //delete dispatcher
    delete dispatcher;

    aiplay->destroy_thread_manager();

    delete model;
    delete model_table;
    delete model_ball;
    delete model_red_blocks;
    delete model_blue_blocks;
    std::cout << "Deletion" << std::endl;
    delete model_blue_hexagon;
    delete model_red_hexagon;
    delete model_neutral_hexagon;
    delete camera;

    for (int i=0; i< models_neutral_hexagon.size(); i++) {
        HexagonObjectPointer* pointer = models_neutral_hexagon[i];
        models_neutral_hexagon[i] = 0;
        delete pointer;
    }

}
//! [6]

//! [9]
void Squircle::sync()
{
    if (!m_renderer) {
        m_renderer = new SquircleRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &SquircleRenderer::init, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &SquircleRenderer::paint, Qt::DirectConnection);
        //m_renderer->squircle = this;
        m_renderer->hex_buttons_enabled = this->hex_buttons_enabled;
        m_renderer->player_colour = this->player_colour;
        m_renderer->aiplay = this->aiplay;
    }


    m_viewportSize = window()->size() * window()->devicePixelRatio();

    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setWindow(window());

    m_renderer->board_length = this->board_length;
    QPointF point =  this->mapFromGlobal(QCursor::pos());


    m_renderer->screenPosX = this->mapFromGlobal(this->position()).toPoint().x();
    m_renderer->screenPosY = this->mapFromGlobal(this->position()).toPoint().y();

    m_renderer->mouseX = point.x();
    m_renderer->mouseY = point.y();
    mouseX = point.x();
    mouseY = point.y();

    this->fps_title = m_renderer->fps_title;

}
//! [9]

void Squircle::keyPressEvent(QKeyEvent *event) {
    QQuickItem::keyPressEvent(event);
    //std::cout << event->key() << " pressed here" << std::endl;
    if(event->key() == Qt::Key_W) {
        m_renderer->press_key_w = 1;
        event->accept();

    }
    else if(event->key() == Qt::Key_A) {
        m_renderer->press_key_a = 1;
        event->accept();

    }
    else if(event->key() == Qt::Key_S) {
        m_renderer->press_key_s = 1;
        event->accept();

    }
    else if(event->key() == Qt::Key_D) {
        m_renderer->press_key_d = 1;
        event->accept();

    }
    else if(event->key() == Qt::Key_Escape) {
        m_renderer->press_key_esc = 1;
        event->accept();

    }
}

void Squircle::keyReleaseEvent(QKeyEvent *event) {
    QQuickItem::keyReleaseEvent(event);
    //std::cout << event->key() << " released here" << std::endl;

    if(event->key() == Qt::Key_W) {
        m_renderer->press_key_w = -1;
        event->accept();
    }
    else if(event->key() == Qt::Key_A) {
        m_renderer->press_key_a = -1;
        event->accept();

    }
    else if(event->key() == Qt::Key_S) {
        m_renderer->press_key_s = -1;
        event->accept();

    }
    else if(event->key() == Qt::Key_D) {
        m_renderer->press_key_d = -1;
        event->accept();

    }
    else if(event->key() == Qt::Key_Escape) {
        m_renderer->press_key_esc = -1;
        inPlayWindow = false; // this variable indicates whether the user has gone into the play window or not (cursor becomes cross hair and is centered on the screen when inside)
        event->accept();

    }
}


void SquircleRenderer::trigger_mouse_click_action() {
    if(!winner_declared && aiplay->turn == player_colour && currently_hovering != nullptr) { // if it is the player's turn to move, perform these actions
        int index = currently_hovering->index;
        if(aiplay->board->is_legal(index%board_length, index/board_length, player_colour)) {
            set_button_colour(index, player_colour);
            prev_hex_colour = player_colour==Colour::BLUE?model_blue_hexagon: model_red_hexagon;
            aiplay->board->make_move(index%board_length, index/board_length, player_colour);
            //std::cout << *aiplay->board << std::endl;
            Colour winner = aiplay->board->has_winner(false);
            if(winner != Colour::EMPTY) {

                if(player_colour == winner) {
                   QMessageBox msg_box(aiplay);
                   msg_box.setInformativeText("You Win!");
                   msg_box.exec();
                    std::cout << "winner" << std::endl;
                }
                else {
                    QMessageBox msg_box(aiplay);
                    msg_box.setInformativeText("You Lose!");
                    msg_box.exec();
                    std::cout << "you lost" << std::endl;

                }
                winner_declared = true;
                aiplay->end_game();


            }
            else {
               aiplay->turn = aiplay->switch_turn(aiplay->turn);
               aiplay->computer_move();
            }
        }

    }
    else if(winner_declared && currently_hovering != nullptr) { // if winner is declared and user presses the mouse, then reset the board
        //aiplay->board = new HexBoard(board_length);
        for (HexagonObjectPointer* obj : models_neutral_hexagon) {
            obj->hexagon_model = model_neutral_hexagon;
        }
        winner_declared = false;
        aiplay->start_game();
        aiplay->set_move();
    }
    else if(can_throw && !winner_declared && aiplay->turn != player_colour) { // if the user is waiting for the computer, allow the user to shoot balls from the eye view
        //Shoot spheres
        btSphereShape* ballShape = new btSphereShape(glm::length(model_ball->meshes[0].vertices[0].position)); //Calculate the radius of the ball model and plugs it into the sphere shape. Model should be centered around the origin for this to work.

        btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
            btQuaternion::getIdentity(),
            btVector3(camera->Position.x,camera->Position.y, camera->Position.z)
        ));

        double initial_velocity = 50;

        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
            0.5,                  // mass, in kg. 0 -> Static object, will never move.
            motionstate,
            ballShape,  // collision shape of body
            btVector3(0,0,0)    // local inertia
        );
        btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);
        rigidBody->setLinearVelocity(btVector3(initial_velocity*camera->Orientation.x,initial_velocity*camera->Orientation.y,initial_velocity*camera->Orientation.z));
        dynamicsWorld->addRigidBody(rigidBody);
        movingRigidBodies.push_back(rigidBody);
        movingRigidBodiesAge.push_back(0);
        QTimer::singleShot(500, this, SLOT(resetsBallThrow()));
        can_throw = false;
        //delete ballShape;
        //delete motionstate;
    }
}

void SquircleRenderer::resetsBallThrow() {
    can_throw = true;
}

// Required for detecting key presses
void Squircle::focusInEvent(QFocusEvent *event) {
    forceActiveFocus();
    event->accept();
}


// Captures mouse clicks and releases
bool Squircle::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && ((QMouseEvent*)event)->button() == Qt::LeftButton)
    {
        QPoint pos = QCursor::pos();
        QWidget *widget = QApplication::widgetAt(pos);
        if (widget != NULL){

            if(std::string(widget->metaObject()->className()).compare("QQuickWidget") == 0) {
                m_renderer->left_mouse_click = 1;

                m_renderer->trigger_mouse_click_action();

                inPlayWindow = true;
                event->accept();
                return true;
            }
            else {
                return false;
            }
        }

    }
    else if(event->type() == QEvent::MouseButtonRelease && ((QMouseEvent*)event)->button() == Qt::LeftButton) {

        if(m_renderer){
            m_renderer->left_mouse_click = -1;
            event->accept();
            return true;
        }

    }

    // Other event type checks here...
    return false;//the signal will be delivered other filters
}

// Sets the button to be a certain colour (on the  3d board)
void SquircleRenderer::set_button_colour(int button_index, Colour c) {

    Model* model_to_assign;
    if(c==Colour::BLUE) {
        model_to_assign = model_blue_hexagon;
    }
    else if(c == Colour::RED) {
        model_to_assign = model_red_hexagon;
    }
    else {
        model_to_assign = model_neutral_hexagon;
    }

    models_neutral_hexagon[button_index]->hexagon_model = model_to_assign;

}


//! [4]
void SquircleRenderer::init()
{
        initializeOpenGLFunctions();

        width = m_viewportSize.width();
        height = m_viewportSize.height();

        if(camera == nullptr) {
            camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
            camera->Position = glm::vec3(0,15,20);

            float scale_offset=0.3f;
            float x_offset = -1.8f;
            float z_offset = 4.5f;
            //run once code
            model_neutral_hexagon = new Model(":/models/hexagon3D/hexagon3D_blender.dae");
            model_red_hexagon = new Model(":/models/hexagon3D/hexagon3D_blender_red.dae");
            model_blue_hexagon = new Model(":/models/hexagon3D/hexagon3D_blender_blue.dae");
            collisionConfiguration = new btDefaultCollisionConfiguration();

             //use the default collision dispatcher. For parallel processing you can use a diffent
            //dispatcher (see Extras/BulletMultiThreaded)
             dispatcher = new btCollisionDispatcher(collisionConfiguration);

             //btDbvtBroadphase is a good general purpose broadphase. You can also try out
            //btAxis3Sweep.
             overlappingPairCache = new btDbvtBroadphase();

             //the default constraint solver. For parallel processing you can use a different solver
            //(see Extras/BulletMultiThreaded)
            solver = new btSequentialImpulseConstraintSolver;

            dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher ,overlappingPairCache ,solver ,collisionConfiguration);

            dynamicsWorld ->setGravity(btVector3(0,-9.8,0));



            //Creates the ground (physics)
            btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
            //	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),50);

            collisionShapes.push_back(groundShape);


            btTransform groundTransform;
            groundTransform.setIdentity();
            groundTransform.setOrigin(btVector3(0, -50, 0));

            {
                btScalar mass(0.);

                //rigidbody is dynamic if and only if mass is non zero, otherwise static
                bool isDynamic = (mass != 0.f);

                btVector3 localInertia(0, 0, 0);
                if (isDynamic)
                    groundShape->calculateLocalInertia(mass, localInertia);

                //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
                btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
                btRigidBody* body = new btRigidBody(rbInfo);
                body->setFriction(1);
                //add the body to the dynamics world
                dynamicsWorld->addRigidBody(body, 10, 1);
                //delete groundShape;
                //delete myMotionState;
            }




            //Creates the board (physics and model instantiation)
            for(int k=0; k< board_length*board_length; k++) {
                int i=k/board_length;
                int j=k%board_length;

                //std::cout << i << "," << j << std::endl;
                models_neutral_hexagon.push_back(new HexagonObjectPointer(model_neutral_hexagon,k));


                double position_x = x_offset + 0.85f*j*scale_offset + 0.425*i*scale_offset;
                double position_y = 5.9f;
                double position_z = z_offset+0.8*scale_offset*i;

                glm::vec3 translation = glm::vec3(position_x, position_y, position_z);
                glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
                glm::vec3 scale = glm::vec3(scale_offset);

                glm::mat4 trans = glm::mat4(1.0f);
                glm::mat4 rot = glm::mat4(1.0f);
                glm::mat4 sca = glm::mat4(1.0f);

                // Use translation, rotation, and scale to change the initialized matrices
                trans = glm::translate(trans, translation);
                rot = glm::mat4_cast(rotation);
                sca = glm::scale(sca, scale);




                hexagon_matrices_meshes.push_back(trans * rot * sca);


                //Translate position by internal matrix for mesh
                glm::vec4 new_tmp_trans = model_neutral_hexagon->matricesMeshes[0] * glm::vec4(position_x, position_y, position_z, 1.0);
                glm::vec3 new_trans = glm::vec3(new_tmp_trans.x, new_tmp_trans.y, new_tmp_trans.z);


            //for(int j=0; j< 5; j++) {
                btConvexHullShape* convexHullCollisionShape = new btConvexHullShape();
                for(int m=0; m< model_neutral_hexagon->meshes[0].vertices.size()-1;m++){
                    glm::vec3 position_convex_hull = model_neutral_hexagon->meshes[0].vertices[m].position;

                    convexHullCollisionShape->addPoint(btVector3(position_convex_hull.x * scale_offset,position_convex_hull.y* scale_offset, position_convex_hull.z* scale_offset), false);
                    //std::cout << model_neutral_hexagon->meshes[0].vertices[m].position.x<< " " << model_neutral_hexagon->meshes[0].vertices[m].position.y << " " <<  model_neutral_hexagon->meshes[0].vertices[m].position.z << std::endl;
                }
                //Add last point and recalculate AABB
                int lastIndex = model_neutral_hexagon->meshes[0].vertices.size()-1;
                glm::vec3 last_position_convex_hull = model_neutral_hexagon->meshes[0].vertices[lastIndex].position;
                convexHullCollisionShape->addPoint(btVector3(last_position_convex_hull.x* scale_offset,last_position_convex_hull.y* scale_offset, last_position_convex_hull.z* scale_offset), true);
                btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
                    btQuaternion::getIdentity(),
                    btVector3(new_tmp_trans.x, new_tmp_trans.y, new_tmp_trans.z)
                ));


                btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                    0,                  // mass, in kg. 0 -> Static object, will never move.
                    motionstate,
                    convexHullCollisionShape,  // collision shape of body
                    btVector3(0,0,0)    // local inertia
                );


                btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);



                rigidBody->setGravity(btVector3(0,-9.8,0));

                dynamicsWorld->addRigidBody(rigidBody);

                //std::cout << dynamicsWorld->getNumCollisionObjects() << std::endl;

                collisionShapes.push_back(convexHullCollisionShape);

                btTransform worldTransform;
                rigidBody->getMotionState()->getWorldTransform(worldTransform);

                //delete convexHullCollisionShape;
                //delete motionstate;


                // Small hack : store the mesh's index "i" in Bullet's User Pointer.
                // Will be used to know which object is picked.
                // A real program would probably pass a "MyGameObjectPointer" instead.
                rigidBody->setUserPointer((void*) models_neutral_hexagon[k]);

                //delete motionstate;
                //std::cout << "here4" << std::endl;

           }
            //for(int i=0; i< dynamicsWorld->getCollisionWorld()->getNumCollisionObjects(); i++){
            //std::cout << dynamicsWorld->getCollisionWorld()->getCollisionObjectArray()[i]->getWorldTransform().getOrigin().getX() << "," << dynamicsWorld->getCollisionWorld()->getCollisionObjectArray()[i]->getWorldTransform().getOrigin().getY() << "," << dynamicsWorld->getCollisionWorld()->getCollisionObjectArray()[i]->getWorldTransform().getOrigin().getZ() << std::endl;
            //}
            //camera->squircle = this->squircle;
        }


        // This example relies on (deprecated) client-side pointers for the vertex
        // input. Therefore, we have to make sure no vertex buffer is bound.


        glViewport(0, 0, width, height);




        // Generates Shader object using shaders default.vert and default.frag
        //if(shaderProgram == nullptr) {
        shaderProgram = new Shader(":/default/default.vert", ":/default/default.frag");
        //}


        // Take care of all the light related things
        glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);




        shaderProgram->Activate();

#ifdef Q_OS_WIN

        PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
        glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");

        PFNGLUNIFORM4FPROC glUniform4f;
        glUniform4f = (PFNGLUNIFORM4FPROC) wglGetProcAddress("glUniform4f");

        PFNGLUNIFORM3FPROC glUniform3f;
        glUniform3f = (PFNGLUNIFORM3FPROC) wglGetProcAddress("glUniform3f");

#endif
        glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);




        glEnable(GL_DEPTH_TEST);

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_FRAMEBUFFER_SRGB);
        // Enables Cull Facing
        //glDisable(GL_CULL_FACE);
        //glEnable(GL_CULL_FACE);
        // Keeps front faces
        //glCullFace(GL_FRONT);
        // Uses counter clock-wise standard
        //glFrontFace(GL_CCW);

}

// This method picks objects from the mouse cursor using Raycast (part of the physics engine)
void SquircleRenderer::pick_object() {

    // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
    glm::vec4 lRayStart_NDC(
        ((float)mouseX/(float)width  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
        ((float)mouseY/(float)height - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
        -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
        1.0f
    );
    glm::vec4 lRayEnd_NDC(
        ((float)mouseX/(float)width  - 0.5f) * 2.0f,
        ((float)mouseY/(float)height - 0.5f) * 2.0f,
        0.0,
        1.0f
    );

    // The Projection matrix goes from Camera Space to NDC.
    // So inverse(ProjectionMatrix) goes from NDC to Camera Space.

    glm::mat4 InverseProjectionMatrix = glm::inverse(camera->projection);

    // The View Matrix goes from World Space to Camera Space.
    // So inverse(ViewMatrix) goes from Camera Space to World Space.
    glm::mat4 InverseViewMatrix = glm::inverse(camera->view);

    glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
    glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
    glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
    glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;

    // Faster way (just one inverse)
    //glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
    //glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
    //glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;

    glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
    lRayDir_world = glm::normalize(lRayDir_world);

    glm::vec3 out_end = camera->Position+ camera->Orientation*1000.0f;

    //dynamicsWorld->updateAabbs();
    //dynamicsWorld->computeOverlappingPairs();

    btVector3 from = btVector3(camera->Position.x, camera->Position.y, camera->Position.z);
    btVector3 to = btVector3(out_end.x, out_end.y, out_end.z);


    btCollisionWorld::ClosestRayResultCallback RayCallback(
        from,
        to
    );
    RayCallback.m_collisionFilterGroup = 20;

    dynamicsWorld->rayTest(
        from,
        to,
        RayCallback
    );
    //std::string message;
    if(RayCallback.hasHit()) {
        //std::ostringstream oss;
        //std::cout << "mesh " << (long)RayCallback.m_collisionObject->getUserPointer() << std::endl;
        //message = oss.str();

        HexagonObjectPointer* obj = ((HexagonObjectPointer*)RayCallback.m_collisionObject->getUserPointer());

        if(obj != nullptr && obj != hexagon_obj) {  // hexagon_obj represents the object the user was hovering on last time the hittest was run
            Model* tmp_model = prev_hex_colour; // prev_hex_colour is the colour of the cell before the mouse cursor entered the area

            prev_hex_colour = obj->hexagon_model;
            if(hexagon_obj != nullptr) {

                if(tmp_model!= nullptr){
                    hexagon_obj->hexagon_model = tmp_model;
                }
            }

            if(obj->hexagon_model==model_neutral_hexagon ){
                obj->hexagon_model = this->player_colour==Colour::BLUE? model_blue_hexagon: model_red_hexagon;
            }
            hexagon_obj = obj;
            currently_hovering = obj;

        }

    }else{
        if(hexagon_obj != nullptr) {

            if(prev_hex_colour!=nullptr) {

                hexagon_obj->hexagon_model = prev_hex_colour;
            }
            hexagon_obj = nullptr;
            currently_hovering = nullptr;
            prev_hex_colour = nullptr;

        }
    }

}


//! [4] //! [5]
void SquircleRenderer::paint()
{
/*
    int current_time = time->currentTime().msecsSinceStartOfDay();
    double timeDiff = (current_time - prev_time) / 1000.0;
    counter++;
*/


    // Play nice with the RHI. Not strictly needed when the scenegraph uses
    // OpenGL directly.
    m_window->beginExternalCommands();

    /*if (timeDiff >= 1.0 / 30 )
    {
        // Creates new title
        std::string FPS = std::to_string((1.0 / timeDiff) * counter);
        std::string ms = std::to_string((timeDiff / counter) * 1000);
        fps_title = "OpenGL - " + FPS + "FPS / " + ms + "ms";
        //std::cout << fps_title << std::endl;
        // Resets times and counter
        prev_time = current_time;
        counter = 0;

    }*/



    glClearColor(0.5f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



    camera->Inputs(this->screenPosX, this->screenPosY, this->mouseX, this->mouseY, this->press_key_esc, this->press_key_w, this->press_key_a, this->press_key_s, this->press_key_d, this->left_mouse_click);
    camera->updateMatrix(45.0f, 0.1f, 500.0f);

    if(hex_buttons_enabled) {
        pick_object();

    }
    float deltaTime = 0.0167;
    float max_age = 0.3f;

    // Steps through the physics simulation with deltaTime and determines which (ball) rigidbodies are past the max_age (and deletes them)s
    dynamicsWorld->stepSimulation(deltaTime,1);

    //std::cout << movingRigidBodies.size() << std::endl;
    //int count = 0;
    auto j=movingRigidBodiesAge.begin();
    for(auto i=movingRigidBodies.begin(); i != movingRigidBodies.end();) {
        btRigidBody* body = *i;
        double age = *j;
        if(age + deltaTime > max_age) {

            if(body && body->getMotionState()) {
                delete body->getMotionState();

            }

            if(body && body->getCollisionShape()) {
                delete body->getCollisionShape();

            }
            movingRigidBodies.erase(i);
            movingRigidBodiesAge.erase(j);
            dynamicsWorld->removeRigidBody(body);


            //delete body->getCollisionShape();

            //delete body;

            //count++;
            continue;
        }
        else {
            *j = *j + deltaTime;

        }

        // Calculates the position and orientation of the physics object and applies them to the opengl object

        btTransform transform;
        body->getMotionState()->getWorldTransform(transform);
        btVector3 position = transform.getOrigin();
        btQuaternion orientation = transform.getRotation();

        glm::quat ori(orientation.w(), orientation.x(), orientation.y(), orientation.z());
        glm::vec3 pos(position.x(),position.y(),position.z());

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        // Use translation, rotation, and scale to change the initialized matrices
        trans = glm::translate(trans, pos);
        rot = glm::mat4_cast(ori);
        sca = glm::scale(sca, glm::vec3(1.0));

        model_ball->Draw(*shaderProgram, *camera, trans*rot*sca);
        i++;
        j++;
        //count++;

    }
    model_table->Draw(*shaderProgram, *camera);
    model->Draw(*shaderProgram, *camera);       // robot model
    model_red_blocks->Draw(*shaderProgram, *camera); // the two red blocks beside the board
    model_blue_blocks->Draw(*shaderProgram, *camera); // the two blue blocks beside the board

    for(int i=0 ; i < board_length ; i++) {
        for (int j=0; j< board_length; j++){
            //if(i==board_length-1 && j==board_length-1) break;
            models_neutral_hexagon[j+i*board_length]->hexagon_model->Draw(*shaderProgram, *camera, hexagon_matrices_meshes[i*board_length+j]);
            //std::cout << hexagon_matrices_meshes[i*board_length+j][0][0] << " " << hexagon_matrices_meshes[i*board_length+j][1][0] << " " << hexagon_matrices_meshes[i*board_length+j][2][0] << " " << hexagon_matrices_meshes[i*board_length+j][3][0] << " " << std::endl;
            //std::cout << hexagon_matrices_meshes[i*board_length+j][0][1] << " " << hexagon_matrices_meshes[i*board_length+j][1][1] << " " << hexagon_matrices_meshes[i*board_length+j][2][1] << " " << hexagon_matrices_meshes[i*board_length+j][3][1] << " " << std::endl;
            //std::cout << hexagon_matrices_meshes[i*board_length+j][0][2] << " " << hexagon_matrices_meshes[i*board_length+j][1][2] << " " << hexagon_matrices_meshes[i*board_length+j][2][2] << " " << hexagon_matrices_meshes[i*board_length+j][3][2] << " " << std::endl;
            //std::cout << hexagon_matrices_meshes[i*board_length+j][0][3] << " " << hexagon_matrices_meshes[i*board_length+j][1][3] << " " << hexagon_matrices_meshes[i*board_length+j][2][3] << " " << hexagon_matrices_meshes[i*board_length+j][3][3] << " " << std::endl;
            //std::cout << std::endl;

        }
    }
    glDisable(GL_BLEND);

    //floor.Draw(shaderProgram, camera);
    //floor.Draw(shaderProgram, *camera);
    //light.Draw(lightShader, *camera);


    //m_program->setUniformValue("t", (float) m_t);

    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    //m_program->disableAttributeArray(0);
    //m_program->release();

    // Not strictly needed for this example, but generally useful for when
    // mixing with raw OpenGL.
    //m_window->resetOpenGLState();
    shaderProgram->Delete();
    delete shaderProgram;
    m_window->endExternalCommands();
}
//! [5]
