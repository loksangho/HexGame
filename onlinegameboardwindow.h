#pragma once

#ifndef ONLINEGAMEBOARDWINDOW_H
#define ONLINEGAMEBOARDWINDOW_H


#include "mainwindow.h"
#include <QTimer>
#include <boost/json/value.hpp>
#include <boost/json.hpp>
#include "hexboardmanager.h"

namespace Ui {
class OnlineGameBoardWindow;
}

class OnlineGameBoardWindow : public QMainWindow, public HexBoardManager
{
    Q_OBJECT

public:
    explicit OnlineGameBoardWindow(QWidget *parent = nullptr);
    ~OnlineGameBoardWindow();
    std::string username = "";
    std::string creator = "";
    std::string opponent = "";
    void show_players();
    int gameid = -1;
    std::string host = "";
    std::string port = "";
    std::string sessionid = "";
    std::string csrftoken = "";
    QTimer* perform_timer;

    Colour player_colour = Colour::EMPTY;

private slots:
    void on_readyBbutton_clicked();
    void perform();
    void cancel();
    void timeout();
    void perform_check_turn();
    void timeout_check_turn();
    void perform_check_colour();
    void timeout_check_colour();

private:
    Ui::OnlineGameBoardWindow *ui;
    void createHexagonalButtons(int length, int size, int x_offset, int y_offset);
    void on_HexagonalButton_clicked(int val);
    void get_host_info_from_file();
    void connect_web_socket_with_text(std::string path, std::string text, std::string* ret_msg);
    void set_colour_turn(Colour c);
    void ready_to_start(boost::json::object v);
    void wait_for_turn();
    void update_board(std::string ret_msg);
    void check_colour();

};




#endif // ONLINEGAMEBOARDWINDOW_H
