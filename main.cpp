#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <iostream>
#include <QQuickWindow>
#include <QFontDatabase>
#include <QOpenGLFunctions>
#include <QLoggingCategory>
#include <QQuickView>
#include <QSGRendererInterface>

int main(int argc, char *argv[])
{

    //QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    QApplication a(argc, argv);
    MainWindow w;

    QFontDatabase::addApplicationFont(":/fonts/Copperplate.ttf");
    QFontDatabase::addApplicationFont(":/fonts/CopperplateBold.ttf");

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);
    QSurfaceFormat glFormat;
    glFormat.setVersion(2,1);
    glFormat.setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

#elif defined(Q_OS_WIN)
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Direct3D11Rhi);
#endif

    //QQuickView *view = new QQuickView;
    //view->setSource(QUrl::fromLocalFile(":/scenegraph/openglunderqml/main.qml"));
    //view->show();


    QFile File(":/qss/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QString(File.readAll());



    a.setStyleSheet(StyleSheet);
    w.show();
    int ret = a.exec();

    return ret;
    //return 0;
}
