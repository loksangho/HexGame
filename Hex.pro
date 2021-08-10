QT       += core gui quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QT += qml quick

CONFIG += qmltypes
QML_IMPORT_NAME = OpenGLUnderQML
QML_IMPORT_MAJOR_VERSION = 1



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boardview3d.cpp \
    camera.cpp \
    connection_metadata.cpp \
    customdialog.cpp \
    ebo.cpp \
    graph.cpp \
    hexboard.cpp \
    hexboardmanager.cpp \
    hexbutton.cpp \
    keyreceiver.cpp \
    main.cpp \
    mainonlinewindow.cpp \
    mainwindow.cpp \
    mesh.cpp \
    model.cpp \
    mywidget.cpp \
    node.cpp \
    onlinegameboardwindow.cpp \
    shaderClass.cpp \
    squircle.cpp \
    stb.cpp \
    texture.cpp \
    vao.cpp \
    vbo.cpp \
    websocket_endpoint.cpp \
    worker.cpp \
    workflowmanager.cpp

HEADERS += \
    Colour.h \
    boardview3d.h \
    camera.h \
    connection_metadata.h \
    customdialog.h \
    ebo.h \
    graph.h \
    hexboard.h \
    hexboardmanager.h \
    hexbutton.h \
    keyreceiver.h \
    mainonlinewindow.h \
    mainwindow.h \
    mesh.h \
    model.h \
    mywidget.h \
    onlinegameboardwindow.h \
    node.h \
    shaderClass.h \
    squircle.h \
    stb_image.h \
    texture.h \
    vao.h \
    vbo.h \
    vertex.h \
    websocket_endpoint.h \
    worker.h \
    workflowmanager.h

FORMS += \
    boardview3d.ui \
    mainonlinewindow.ui \
    mainwindow.ui \
    onlinegameboardwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    appearance.qrc \
    hexagon_btn.qrc \
    host_info.qrc \
    openglunderqml.qrc \
    shaders.qrc


macx {

    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_CXXFLAGS += -I/usr/local/opt/openssl/include

    _BOOST_PATH = /usr/local/Cellar/boost/1.76.0
    _ASSIMP_PATH = /usr/local/Cellar/assimp/5.0.1
    _BULLET_PATH = /usr/local/Cellar/bullet/3.17
    INCLUDEPATH += "$${_BOOST_PATH}/include/"
    INCLUDEPATH += "./websocketpp/"
    INCLUDEPATH += "./glm/"
    INCLUDEPATH += "./json/"
    INCLUDEPATH += "$${_ASSIMP_PATH}/include/"
    INCLUDEPATH += "$${_BULLET_PATH}/include/bullet"

    LIBS += -L$${_BOOST_PATH}/lib
    LIBS += -L$${_ASSIMP_PATH}/lib
    LIBS += -L$${_BULLET_PATH}/lib
    LIBS += -L/usr/local/opt/openssl/lib
    LIBS += -lboost_system -lssl -lcrypto -lcurl -lassimp -lBulletDynamics -lBulletCollision -lBulletSoftBody -lLinearMath
    LIBS += -lz -lc++ -lSystem.B

}

unix {
    QT_QPA_PLATFORM=wayland

    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -static-libgcc

    INCLUDEPATH += /usr/include/assimp
    INCLUDEPATH += /usr/include/bullet
    INCLUDEPATH += /usr/include/curl
    INCLUDEPATH += /usr/include/GL
    INCLUDEPATH += /home/loksangho/boost_1_76_0
    INCLUDEPATH += /home/loksangho/bullet3/src
    INCLUDEPATH += "./websocketpp/"
    INCLUDEPATH += "./glm/"
    INCLUDEPATH += "./json/"

    LIBS += -L/home/loksangho/boost_1_76_0/stage/lib
    LIBS += -lboost_system -lcurl -lassimp -lBulletDynamics -lBulletCollision -lBulletSoftBody -lLinearMath -lGL
}

win32 {
    #QMAKE_CXXFLAGS += -D_WIN32_WINNT=0x0601

    INCLUDEPATH += "C:/Users/loksa/Documents/Hex/glm/"
    INCLUDEPATH += "C:/Users/loksa/Documents/Hex/websocketpp/"
    INCLUDEPATH += "C:/Users/loksa/Documents/Hex/json/include/nlohmann"
    INCLUDEPATH += "C:/msys64/mingw64/include/"
    INCLUDEPATH += "C:/msys64/mingw64/include/bullet/"

    LIBS += -LC:/msys64/mingw64/lib
    LIBS += -llibboost_system-mt -llibboost_thread-mt -lopengl32 -lcurl -lassimp -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lws2_32 -lwsock32
    #LIBS += -llibboost_system-vc142-mt-gd-x64-1_76 -llibEGL.dll -llibGLESv2.dll -llibcurl -lassimp-vc142-mt -lBulletDynamics -lBulletSoftBody -lBulletCollision -lLinearMath

}

DISTFILES += \
    default.frag \
    default.vert \
    light.frag \
    light.vert





