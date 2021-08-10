#pragma once

#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void paintEvent(QPaintEvent * e);
};

#endif // MYWIDGET_H
