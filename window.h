#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include "qglobal.h"
#ifdef Q_OS_WIN
    #include "GLES2/gl2.h"
    #include "GLES2/gl2ext.h"
#elif defined(Q_OS_MACX) || defined(Q_OS_LINUX)
    #include<QtGui/QOpenGLFunctions>
#endif

class Window : public QOpenGLWindow
{
  Q_OBJECT

// OpenGL Events
public:
  ~Window();

  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
  void teardownGL();

private:
  // Private Helpers
  void printContextInformation();
};

#endif // WINDOW_H
