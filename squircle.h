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

#ifndef SQUIRCLE_H
#define SQUIRCLE_H

/*
 *  This is the main class handling the 3D mode of the game. It is so-named because it is based on the example from the Qt website.
 *
 */

#include "qglobal.h"

#ifdef Q_OS_WIN
    #include<QtGui/QOpenGLFunctions>
    #include <d3d11.h>
    #include <d3dcompiler.h>
    #include "d3d11shaderclass.h"
    #include "d3d11texture.h"
    #include "d3d11mesh.h"
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include<QtGui/QOpenGLFunctions>
#endif

#include <QtQuick/QQuickItem>
#include <QOpenGLShaderProgram>

#include <QtQuick/qquickwindow.h>
#include <QTime>
#include "camera.h"
#include <QWidget>
#include <QCursor>
#include <QGuiApplication>
#include "model.h"
#include <LinearMath/btVector3.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
#include "mainwindow.h"



QT_FORWARD_DECLARE_CLASS(Squircle)

class AIPlay : public MainWindow
{
    Q_OBJECT

public:
    AIPlay(Squircle* squircle, Colour player_colour, int difficulty);
    virtual void handleResults(const QString &str) override;
    virtual void set_button_colour(int button_index, Colour c) override;
    virtual void set_enable_buttons(bool b) override;
    //virtual void setup_thread_manager() override;

private:
    Squircle* squircle;
};

class HexagonObjectPointer {
public:
    Model* hexagon_model;
    int index;
    HexagonObjectPointer(Model* model, int index) : hexagon_model(model), index(index) {}
};

//! [1]
class SquircleRenderer : public QObject
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
        , protected QOpenGLFunctions
#endif
{
    Q_OBJECT


public:
    SquircleRenderer();
    ~SquircleRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }
    void pick_object();
    void set_button_colour(int button_index, Colour c);
    void set_enable_buttons(bool b);
    void trigger_mouse_click_action();
    double mouseX = 100.0;
    double mouseY = 100.0;
    int screenPosX = 0.0;
    int screenPosY = 0.0;
    QQuickWindow *m_window;
    Camera* camera = nullptr;
    Shader* shaderProgram = nullptr;
    Model* model;
    Model* model2;
    Model* model_table;
    Model* model_red_blocks;
    Model* model_blue_blocks;
    Model* model_ball;
    Model* model_neutral_hexagon;
    std::vector<glm::mat4 > hexagon_matrices_meshes;
    Model* model_red_hexagon;
    Model* model_blue_hexagon;
    QVector<HexagonObjectPointer*> models_neutral_hexagon;
    int press_key_w = -1; // -1 means released, 1 means pressed
    int press_key_a = -1;
    int press_key_s = -1;
    int press_key_d = -1;
    int press_key_esc = -1;
    int left_mouse_click = -1;
    std::string fps_title;
    int board_length;
    Colour player_colour;
    QSize m_viewportSize;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btCollisionWorld* collisionWorld;
    std::vector<btCollisionShape *> collisionShapes;
    std::vector<btRigidBody *> movingRigidBodies;
    std::vector<double> movingRigidBodiesAge;
    HexagonObjectPointer* hexagon_obj = nullptr;
    bool hex_buttons_enabled = false;
    AIPlay* aiplay;
    Model* prev_hex_colour = nullptr;
    HexagonObjectPointer* currently_hovering = nullptr;
    bool winner_declared = false;
    bool can_throw = true;
    QSize mouse_viewportSize;

#ifdef Q_OS_WIN
    struct TargaHeader
        {
            unsigned char data1[12];
            unsigned short width;
            unsigned short height;
            unsigned char bpp;
            unsigned char data2;
        };
    ID3D11Device *m_device = nullptr;
    ID3D11DeviceContext *m_context = nullptr;

    D3D11Shader* d3d11ShaderProgram = nullptr;
    bool m_initialized = false;

#endif

public slots:
    void init();
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    void paint();
#endif
    void resetsBallThrow();
#ifdef Q_OS_WIN
    void frameStart();
    void mainPassRecordingStart();
#endif

private:
    qreal m_t;
    QOpenGLShaderProgram *m_program;
    float rotation = 0.0f;
    QTime* time;
    int prev_time = 0;
    unsigned int counter = 0;

#ifdef Q_OS_WIN
    void D3D11Init();
#endif

};
//! [1]

//! [2]
class Squircle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
    QML_ELEMENT

public:
    Squircle();

    QSize m_viewportSize;

    qreal t() const { return m_t; }
    void setT(qreal t);
    double mouseX = 100.0;
    double mouseY = 100.0;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent * event) override;
    std::string fps_title;
    void init(int length, Colour player_colour, int difficulty);
    int board_length;
    Colour player_colour;
    AIPlay* aiplay;
    void set_button_colour(int button_index, Colour c);
    void set_enable_buttons(bool b);
    bool hex_buttons_enabled = false;
    bool inPlayWindow = false;
    void changeMouseSensitivity(int val);
    void changeMoveSpeed(int val);

signals:
    void tChanged();
    void mouseChanged();
public slots:
    void sync();
    void cleanup();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    void releaseResources() override;
    QCursor cursor;
    qreal m_t;
    SquircleRenderer *m_renderer;
};
//! [2]



#endif // SQUIRCLE_H

