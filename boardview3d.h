#ifndef BOARDVIEW3D_H
#define BOARDVIEW3D_H

#include <QWidget>
#include <QMainWindow>
#include "squircle.h"

namespace Ui {
class BoardView3D;
}

class BoardView3D : public QWidget
{
    Q_OBJECT

public:
    explicit BoardView3D(QMainWindow* main_window, QWidget *parent = nullptr);
    ~BoardView3D();
    QMainWindow* main_window;



private slots:
    void on_pushButton_clicked();

private:
    Ui::BoardView3D *ui;
    Squircle testObj;
};

#endif // BOARDVIEW3D_H
