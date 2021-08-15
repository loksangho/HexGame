#pragma once

#ifndef MAINONLINEWINDOW_H
#define MAINONLINEWINDOW_H

/*
 *  This is class that handles the online aspect of the game.
 *
 */

#include <QMainWindow>
#include <QProgressDialog>
#include <QItemSelection>



namespace Ui {
class MainOnlineWindow;
}

class MainOnlineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainOnlineWindow(QWidget *parent = nullptr);
    ~MainOnlineWindow();
    std::string host = "aqueous-temple-80210.herokuapp.com";
    //std::string host = "localhost";
    std::string port = "80";
    std::string sessionid = "";
    std::string username = "";
    std::string csrftoken = "";
    QTimer* t;
    QProgressDialog* progress;
    QTimer* perform_timer;
    int cur_game_id = -1;

private slots:
    void on_pushButton_clicked();
    void get_host_info_from_file();
    void check_lobby(std::string sessionid);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_refreshLobbyButton_clicked();
    void selectionChangedSlot(const QItemSelection & selected, const QItemSelection & deselected);

    void on_joinGameButton_clicked();

    void on_registerAccountButton_clicked();

    void on_logoutButton_clicked();
    void connect_web_socket_with_text(std::string path, std::string text, std::string* ret_msg);
    void perform();
    void cancel();
    void timeout();
    void write_login_to_file(std::string username, std::string password);


private:
    Ui::MainOnlineWindow *ui;
};

#endif // MAINONLINEWINDOW_H
