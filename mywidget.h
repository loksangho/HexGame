#pragma once

#ifndef MYWIDGET_H
#define MYWIDGET_H

/*
 *  This class draws the blue and red side bars to the board in a dynamic way.
 *
 */

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void paintEvent(QPaintEvent * e);
};

#endif // MYWIDGET_H
