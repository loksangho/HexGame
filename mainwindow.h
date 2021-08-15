#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 *  This is the class that is the main window of the game. It handles the 2D play with AI functionality as well.
 *
 */

#include <QMainWindow>
#include "hexboard.h"
#include "hexbutton.h"
#include <QThread>
#include "worker.h"
#include "mywidget.h"
#include "hexboardmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow, public HexBoardManager
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    //int length=11;
    ~MainWindow();

    void setup_object();
    void computer_move();
    void destroy_thread_manager();
    void set_move();
    Colour player_colour;
    QString player_name;
    int mc_trials=50;

public slots:
    virtual void handleResults(const QString &);

signals:
    void operate(const QString &, HexBoard* board, Colour c, int mc_trials);

private slots:
    void on_startGameButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


protected:
    QThread workerThread;
    void on_HexagonalButton_clicked(int val);


    virtual void setup_thread_manager();


private:
    void createHexagonalButtons(int length, int size, int x_offset, int y_offset);
    Ui::MainWindow *ui;
    void setupStyleSheet();
    void set_colour_turn(Colour c);


};
#endif // MAINWINDOW_H
