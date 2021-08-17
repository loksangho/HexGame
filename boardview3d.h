#ifndef BOARDVIEW3D_H
#define BOARDVIEW3D_H

/*
 *  This class provides a window for the 3D mode of the game.
 *
 */

#include <QWidget>
#include <QMainWindow>
#include "squircle.h"
#include "overlaywidgetclass.h"

namespace Ui {
class BoardView3D;
}

class BoardView3D : public QWidget
{
    Q_OBJECT

public:
    explicit BoardView3D(QMainWindow* main_window, QWidget *parent = nullptr);
    void init(int board_length, int colour, int difficulty);
    ~BoardView3D();
    QMainWindow* main_window = nullptr;
    Squircle* squircle = nullptr;
    //ContainerWidget* base = nullptr;
    //CrossHairOverlay* crosshair = nullptr;

private slots:
    void on_pushButton_clicked();

    void on_mouseSensitivitySlider_valueChanged(int value);

    void on_moveSpeedSlider_valueChanged(int value);

private:
    Ui::BoardView3D *ui;
    Squircle* testObj;
};

#endif // BOARDVIEW3D_H
