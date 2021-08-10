#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <iostream>
#include <QQuickWindow>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QSurfaceFormat glFormat;
    glFormat.setVersion(1, 0);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);




    QApplication a(argc, argv);
    MainWindow w;

    QFontDatabase::addApplicationFont(":/fonts/Copperplate.ttf");
    QFontDatabase::addApplicationFont(":/fonts/CopperplateBold.ttf");

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

    QFile File(":/qss/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QString(File.readAll());

    a.setStyleSheet(StyleSheet);
    w.show();
    int ret = a.exec();

    return ret;
    //return 0;
}
