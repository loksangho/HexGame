
#include "mainonlinewindow.h"
#include "ui_mainonlinewindow.h"
#include "mainwindow.h"
#include <QItemSelection>
#include <onlinegameboardwindow.h>
#include <QFile>
#include <QStandardPaths>
#include <QTimer>
#include <QProgressDialog>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include "boost/property_tree/ptree.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <utility>
#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "customdialog.h"
#include <boost/json/value.hpp>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <boost/algorithm/string/trim.hpp>
#include <boost/exception/exception.hpp>
#include <QProgressDialog>
#include "websocket_endpoint.h"
#include "connection_metadata.h"
#include <QProcess>





size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Gets the host name and port number from the file inside the resource qrc
void MainOnlineWindow::get_host_info_from_file() {
    QFile file(":/info/hostinfo.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("=");


        if(fields.at(0).compare("host")==0){
            this->host = (fields.at(1)).toStdString();
        }
        if(fields.at(0).compare("port")==0){
            this->port = (fields.at(1)).toStdString();
        }

    }

    file.close();
}

// Helper functions to split string
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

QVector<std::string> split(const std::string &s, char delim) {
    QVector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

// Checks lobby for any available games
void MainOnlineWindow::check_lobby(std::string sessionid) {

    if(sessionid=="") {
        QStandardItemModel* standardModel = new QStandardItemModel(ui->listView);
        ui->listView->setModel(standardModel);
        return;
    }


    std::string docbuf2;
    std::string next = "/game/lobby/";
    int err;
    char curl_errbuf[CURL_ERROR_SIZE];
    CURL *curl3 = curl_easy_init();
    curl_easy_setopt(curl3, CURLOPT_URL, std::string("https://").append(host).append(next).c_str());
    curl_easy_setopt(curl3, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl3, CURLOPT_ERRORBUFFER, curl_errbuf);
    curl_easy_setopt(curl3, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl3, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl3, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl3, CURLOPT_COOKIE, std::string("sessionid=").append(sessionid).c_str());


    curl_easy_setopt(curl3, CURLOPT_WRITEDATA, &docbuf2);
    err = curl_easy_perform(curl3);
    curl_easy_cleanup(curl3);

    std::cout << docbuf2 << std::endl;

    boost::json::value val = boost::json::parse( docbuf2 );
    boost::json::object v = val.as_object();
    boost::json::array arr = v["available_games"].as_array();

    QStandardItemModel* standardModel = new QStandardItemModel(ui->listView);
    QStandardItem *rootNode = standardModel->invisibleRootItem();


    QStandardItem *cur_item;
    for (boost::json::value game : arr) {
        cur_item = new QStandardItem("America");

        boost::json::string creator = game.as_object()["creator"].as_string();
        int id = game.as_object()["id"].as_int64();

        cur_item = new QStandardItem(std::string(creator.c_str()).append(" : ").append(std::to_string(id)).c_str());


        rootNode->    appendRow(cur_item);
    }

    //selection changes shall trigger a slot
    ui->listView->setModel(standardModel);
    QItemSelectionModel *selectionModel = ui->listView->selectionModel();

    connect(selectionModel, &QItemSelectionModel::selectionChanged,
                this, &MainOnlineWindow::selectionChangedSlot);


}

// When the selection of the available game in the selection list is changed, this is called
void MainOnlineWindow::selectionChangedSlot(const QItemSelection & selected, const QItemSelection & deselected) {

    ui->joinGameButton->setEnabled(true);
}

MainOnlineWindow::MainOnlineWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainOnlineWindow)
{
    ui->setupUi(this);
    ui->logoutButton->hide();
    ui->pushButton_3->setEnabled(false);
    ui->refreshLobbyButton->setEnabled(false);
}

MainOnlineWindow::~MainOnlineWindow()
{
    delete ui;
}

// This is the button that is goes back to the 'play with AI' mode, aka the main window.
void MainOnlineWindow::on_pushButton_clicked()
{
    MainWindow* main_window = new MainWindow();
    this->close();
    main_window->show();
}


// This is when the login button is pressed
void MainOnlineWindow::on_pushButton_2_clicked() //login pressed
{

    ui->pushButton_2->setEnabled(false);
    std::string username     = "";
    std::string password      = "";

    QFile file(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/login.txt"));
    std::cout << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/login.txt").toStdString() << std::endl;
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("=");


        if(fields.at(0).compare("username")==0){
            username = (fields.at(1)).toStdString();
        }
        if(fields.at(0).compare("password")==0){
            password = (fields.at(1)).toStdString();
        }

    }

    file.close();


    get_host_info_from_file();

    CustomDialog d("Login Window", this);
    d.addLabel    ("Please place in your login credentials here");
    d.addLineEdit ("Username:  ", &username, "Enter username here...");
    d.addLineEdit ("Password:  ", &password, "Enter username here...", true);

    d.exec();                    // Execution stops here until user closes dialog

    if(d.wasCancelled()) {
        std::cout << "You have cancelled your login" << std::endl;
        return;
    }


    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();

    std::string readBuffer;
    char curl_errbuf[CURL_ERROR_SIZE];





    int err;
    curl_easy_setopt(curl, CURLOPT_URL, std::string("https://").append(host).append("/accounts/login/").c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    err = curl_easy_perform(curl);




    struct curl_slist *cookies;
    curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
    std::string csrfmiddlewaretoken="";

    std::string csrftoken = "";
    std::string next = "/game/lobby/";

    if(cookies) {
        std::cout << "cookies available" << std::endl;
        struct curl_slist *cur_cookie;
        int i=1;
        cur_cookie = cookies;
        do{
            std::cout << "Data:" << cur_cookie->data << std::endl;

            QVector<std::string> words = split(std::string(cur_cookie->data), '\t');

            if(words[5].compare("csrftoken") == 0) {
                csrftoken=words[6];
            }

            cur_cookie = cur_cookie->next;
            //std::cout << i++ << std::endl;
        } while(cur_cookie);
    }
    else {
        std::cout << "cookies empty" << std::endl;

    }

    this->csrftoken = csrftoken;

    curl_slist_free_all(cookies);
    curl_easy_cleanup(curl);


    int res;
    CURL *curl2 = curl_easy_init();
    struct curl_slist *list2 = NULL;
    list2 = curl_slist_append(list2, std::string("X-CSRFToken: ").append(csrftoken).c_str());
    curl_easy_setopt(curl2, CURLOPT_URL, std::string("https://").append(host).append("/accounts/login/").c_str());

    std::cout << std::string("https://").append(host).append("/accounts/login").c_str() << std::endl;
    curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, std::string("csrfmiddlewaretoken=").append(csrfmiddlewaretoken).append("&next=").append(next.c_str()).c_str());
    curl_mime *mime;
    curl_mimepart *username_part;
    curl_mimepart *password_part;
    curl_mimepart *next_part;

     /* Build an HTTP form with a single field named "data", */
    mime = curl_mime_init(curl2);
    username_part = curl_mime_addpart(mime);
    curl_mime_data(username_part, username.c_str(), CURL_ZERO_TERMINATED);
    curl_mime_name(username_part, "username");

    password_part = curl_mime_addpart(mime);
    curl_mime_data(password_part, password.c_str(), CURL_ZERO_TERMINATED);
    curl_mime_name(password_part, "password");

    next_part = curl_mime_addpart(mime);
    curl_mime_data(next_part, next.c_str(), CURL_ZERO_TERMINATED);
    curl_mime_name(next_part, "next");



     /* Post and send it. */
     curl_easy_setopt(curl2, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl2, CURLOPT_COOKIE, std::string("csrftoken=").append(csrftoken).c_str());
    curl_easy_setopt(curl2, CURLOPT_HTTPHEADER, list2);
    curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl2, CURLOPT_COOKIEFILE, "");

    res = curl_easy_perform(curl2);

    struct curl_slist *cookies2;
    curl_easy_getinfo(curl2, CURLINFO_COOKIELIST, &cookies2);
    sessionid = "";
    if(cookies2) {
        std::cout << "cookies available" << std::endl;
        struct curl_slist *cur_cookie2;
        cur_cookie2 = cookies2;
        do{
            std::cout << "Data:" << cur_cookie2->data << std::endl;

            QVector<std::string> words = split(std::string(cur_cookie2->data), '\t');

            if(words[5].compare("sessionid") == 0) {
                sessionid=words[6];
            }

            cur_cookie2 = cur_cookie2->next;
            //std::cout << i++ << std::endl;
        } while(cur_cookie2);
    }
    else {
        std::cout << "cookies empty" << std::endl;

    }

    curl_easy_cleanup(curl2);


    if(sessionid.compare("") != 0){
        this->username = username;
        write_login_to_file(username,password);

        ui->logoutButton->show();
        ui->pushButton_2->hide();
        ui->pushButton_3->setEnabled(true);
        ui->refreshLobbyButton->setEnabled(true);
        ui->loggedInStatus->setText(std::string("Logged in as: ").append(username).c_str());

    }
    else {
        ui->pushButton->setEnabled(true);
    }
    check_lobby(sessionid);

}


// This function writes the login information to a particular 'safe' location when player successfully logins
void MainOnlineWindow::write_login_to_file(std::string username, std::string password) {
    QFile file(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/login.txt"));
    QDir dir;
    if(!dir.exists(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))) {
        dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
        qDebug()<<"directory now exists";
    }
    if ( file.open(QIODevice::ReadWrite) )
    {
        qDebug()<<"file now exists";
        QString mystring = "username=";
        mystring = mystring.append(QString::fromStdString(username)).append("\n").append("password=").append(QString::fromStdString(password));
        file.write(mystring.toUtf8());
        file.close();
    }
}

// This is called when player clicks on 'Create Game'
void MainOnlineWindow::on_pushButton_3_clicked() //create game pressed
{

    ui->pushButton_3->setEnabled(false);
    get_host_info_from_file();
    std::string data = "{\"action\": \"create_game\", \"user\":\"";
    data = data.append(this->username).append("\"}");


    auto const path = std::string("/ws/play/");
    auto const text = data;

     std::string ret_msg;

     connect_web_socket_with_text(path.c_str(), text.c_str(), &ret_msg);
     //std::cout << "Connect Success" << std::endl;

     //std::cout << "ret_msg: " << ret_msg << std::endl;
     boost::json::value val = boost::json::parse( ret_msg );
     boost::json::object v = val.as_object();
     boost::json::string state = v["state"].as_string();
     int game_id = v["game_id"].as_int64();
     this->cur_game_id = game_id;

     progress = new QProgressDialog("Waiting for player to join", "Abort Game", 0, 100, this);
     progress->setWindowModality(Qt::WindowModal);
     connect(progress, SIGNAL(canceled()), this, SLOT(cancel()));
     QTimer::singleShot(0, this, SLOT(perform()));

}

// This starts a timer to check if other player has joined the created game
void MainOnlineWindow::perform() {
    perform_timer = new QTimer(this);
    connect(perform_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    perform_timer->start(5000); // number of milliseconds between checks
}

void MainOnlineWindow::timeout() {
    // Check if other player have joined
    std::string ret_msg;

    connect_web_socket_with_text("/ws/play/", std::string("{ \"action\":\"check_joined\" , \"game_id\" : ").append(std::to_string(this->cur_game_id)).append("}"), &ret_msg);

    //std::cout <<  "ret_msg: " << ret_msg << std::endl;

    boost::json::value val = boost::json::parse( ret_msg );
    boost::json::object v = val.as_object();
    boost::json::string state = v["state"].as_string();
    if(state.compare("someone has joined") == 0) {
        //someone has joined
        perform_timer->stop();
        boost::json::string opponent = v["opponent"].as_string();
        OnlineGameBoardWindow* online_game_board_window = new OnlineGameBoardWindow();
        online_game_board_window->creator = username;
        online_game_board_window->username = username;
        online_game_board_window->opponent = std::string(opponent.c_str());
        online_game_board_window->sessionid = sessionid;
        online_game_board_window->csrftoken = csrftoken;
        online_game_board_window->gameid = this->cur_game_id;
        online_game_board_window->show_players();
        online_game_board_window->show();
        progress->close();
    }

}

// When player who started a game clicks cancel, the game is deleted from the database
void MainOnlineWindow::cancel() {

    perform_timer->stop();

    std::string ret_msg;
    connect_web_socket_with_text("/ws/play/", std::string("{ \"action\":\"end_game\" , \"game_id\" : ").append(std::to_string(this->cur_game_id)).append("}"), &ret_msg);

    boost::json::value val = boost::json::parse( ret_msg );
    boost::json::object v = val.as_object();
    boost::json::string state = v["state"].as_string();
    if(state.compare("game ended") == 0) {
        ui->textEdit->setText("Game deleted");
    }
    ui->pushButton_3->setEnabled(true);

}

// This function writes text to the server using web socket
void MainOnlineWindow::connect_web_socket_with_text(std::string path, std::string text, std::string* ret_msg) {

    get_host_info_from_file();
    std::string host = this->host;
    std::string port = this->port;

    // The io_context is required for all I/O
    websocket_endpoint endpoint;

    int id = endpoint.connect(std::string("ws://").append(host).append(path), text, this->sessionid, this->csrftoken, ret_msg);
    if (id != -1) {
        std::cout << "> Created connection with id " << id << std::endl;
    }
    return;

}

// When the player refreshes the lobby
void MainOnlineWindow::on_refreshLobbyButton_clicked()
{
    check_lobby(sessionid);
}


void MainOnlineWindow::on_joinGameButton_clicked()
{
    get_host_info_from_file();
    auto index = ui->listView->selectionModel()->currentIndex();
    QVariant value = index.sibling(index.row(),index.column()).data();
    QVector<std::string> split_words = split(value.toString().toStdString(), ':');
    std::string game_id_str = split_words[1];
    boost::algorithm::trim(game_id_str);
    int game_id = stoi(game_id_str);

    std::cout << game_id << std::endl;

    std::string docbuf2;
    int err;
    char curl_errbuf[CURL_ERROR_SIZE];
    CURL *curl3 = curl_easy_init();
    curl_easy_setopt(curl3, CURLOPT_URL, std::string("https://").append(host).append("/game/play/").append(std::to_string(game_id)).c_str());
    curl_easy_setopt(curl3, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl3, CURLOPT_ERRORBUFFER, curl_errbuf);
    curl_easy_setopt(curl3, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl3, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl3, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl3, CURLOPT_COOKIE, std::string("sessionid=").append(sessionid).c_str());


    curl_easy_setopt(curl3, CURLOPT_WRITEDATA, &docbuf2);
    err = curl_easy_perform(curl3);
    curl_easy_cleanup(curl3);


    //std::cout << docbuf2 << std::endl;

    boost::json::value val = boost::json::parse( docbuf2 );
    boost::json::object v = val.as_object();

    if(v["message"].as_string().compare("player_is_creator") == 0) {
        // cannot join because you are the creator
        QMessageBox msgBox;
        msgBox.setText("You are already part of this game so you can't join it again.");
        msgBox.exec();



    }
    else if (v["message"].as_string().compare("set_opponent_as_user") == 0 ) {
        // sets opponent as user, starts game
        OnlineGameBoardWindow* online_game_window = new OnlineGameBoardWindow();
        online_game_window->username = this->username;
        std::string creator = std::string(v["game"].as_object()["creator"].as_object()["username"].as_string().c_str());
        std::string opponent = std::string(v["game"].as_object()["opponent"].as_object()["username"].as_string().c_str());
        online_game_window->creator = creator;
        online_game_window->opponent = opponent;
        online_game_window->gameid = game_id;
        online_game_window->sessionid = sessionid;
        online_game_window->csrftoken = csrftoken;
        online_game_window->show_players();
        online_game_window->show();

        //auto const path = std::string("/ws/play/").append(this->username).append("/").append(std::to_string(game_id)).append("/").c_str();


    }
    else if(v["message"].as_string().compare("game_not_available") == 0) {
        // game not available (completed or full)
        QMessageBox msgBox;
        msgBox.setText("This game is not available. It might already be completed or it is fully occupied.");
        msgBox.exec();
    }
}


void MainOnlineWindow::on_registerAccountButton_clicked()
{
    std::string username     = "username";
    std::string password      = "password";
    std::string password1     = "password";

    get_host_info_from_file();

    CustomDialog d("Registration Window", this);
    d.addLabel    ("Please register your details here:");
    d.addLineEdit ("Username:  ", &username, "Enter username here...");
    d.addLineEdit ("Password:  ", &password, "Enter username here...", true);
    d.addLineEdit ("Enter Password Again:  ", &password1, "Enter username here...", true);


    while(true) {
        d.exec();                    // Execution stops here until user closes dialog

        if(d.wasCancelled()) {
            QMessageBox msgBox;
            msgBox.setText("You have cancelled your registration.");
            msgBox.exec();
            return;
        }

        curl_global_init(CURL_GLOBAL_ALL);
        CURL *curl = curl_easy_init();

        std::string readBuffer;
        char curl_errbuf[CURL_ERROR_SIZE];

        int err;
        curl_easy_setopt(curl, CURLOPT_URL, std::string("https://").append(host).append("/game/register/").c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");



        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        err = curl_easy_perform(curl);

        //std::cout << "docbuf: " << readBuffer.size() << std::endl;
        struct curl_slist *cookies;
        curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
        std::string csrfmiddlewaretoken="";

        std::string csrftoken = "";
        std::string next = "/game/register_success/";

        if(cookies) {
            //std::cout << "cookies available" << std::endl;
            struct curl_slist *cur_cookie;
            cur_cookie = cookies;
            do{
                //std::cout << "Data:" << cur_cookie->data << std::endl;

                QVector<std::string> words = split(std::string(cur_cookie->data), '\t');

                if(words[5].compare("csrftoken") == 0) {
                    csrftoken=words[6];
                }

                cur_cookie = cur_cookie->next;
                //std::cout << i++ << std::endl;
            } while(cur_cookie);
        }
        else {
            std::cout << "cookies empty" << std::endl;
        }
        //std::cout << "csrftoken: " << csrftoken << std::endl;
        curl_slist_free_all(cookies);
        curl_easy_cleanup(curl);
         //get token here

        //std::cout << "csrftoken: " << csrftoken << std::endl;

        int res;
        CURL *curl3 = curl_easy_init();
        struct curl_slist *list3 = NULL;
        list3 = curl_slist_append(list3, std::string("X-CSRFToken: ").append(csrftoken).c_str());
        curl_easy_setopt(curl3, CURLOPT_URL, std::string("https://").append(host).append("/game/register/").c_str());
        curl_easy_setopt(curl3, CURLOPT_POSTFIELDS, std::string("csrfmiddlewaretoken=").append(csrfmiddlewaretoken).c_str());
        curl_mime *mime;
        curl_mimepart *username_part;
        curl_mimepart *password1_part;
        curl_mimepart *password2_part;

         /* Build an HTTP form with a single field named "data", */
        mime = curl_mime_init(curl3);
        username_part = curl_mime_addpart(mime);
        curl_mime_data(username_part, username.c_str(), CURL_ZERO_TERMINATED);
        curl_mime_name(username_part, "username");

        password1_part = curl_mime_addpart(mime);
        curl_mime_data(password1_part, password.c_str(), CURL_ZERO_TERMINATED);
        curl_mime_name(password1_part, "password1");

        password2_part = curl_mime_addpart(mime);
        curl_mime_data(password2_part, password1.c_str(), CURL_ZERO_TERMINATED);
        curl_mime_name(password2_part, "password2");

        //std::cout << "username: " << username << std::endl;

        //std::cout << "password1: " << password << std::endl;

        //std::cout << "password2: " << password1 << std::endl;

         /* Post and send it. */
        curl_easy_setopt(curl3, CURLOPT_MIMEPOST, mime);
        curl_easy_setopt(curl3, CURLOPT_COOKIE, std::string("csrftoken=").append(csrftoken).c_str());
        curl_easy_setopt(curl3, CURLOPT_HTTPHEADER, list3);
        curl_easy_setopt(curl3, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl3, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl3, CURLOPT_COOKIEFILE, "");

        res = curl_easy_perform(curl3);
        //std::cout << readBuffer.size() << std::endl;


        struct curl_slist *cookies2;
        curl_easy_getinfo(curl3, CURLINFO_COOKIELIST, &cookies2);
        sessionid = "";
        if(cookies2) {
            std::cout << "cookies available2" << std::endl;
            struct curl_slist *cur_cookie2;
            cur_cookie2 = cookies2;
            int i=0;
            while(cur_cookie2){
                std::cout << "Data:" << cur_cookie2->data << std::endl;

                QVector<std::string> words = split(std::string(cur_cookie2->data), '\t');

                if(words[5].compare("sessionid") == 0) {
                    sessionid=words[6];
                }
                cur_cookie2 = cur_cookie2->next;
                std::cout << i++ << std::endl;
            }
        }
        else {
            std::cout << "cookies empty" << std::endl;
        }

        curl_easy_cleanup(curl3);


        //std::cout << "next: " << next << std::endl;

        //std::cout << readBuffer.size() << std::endl;

        //std::cout << sessionid << std::endl;

        //std::cout << readBuffer << std::endl;

        if(sessionid.compare("") != 0) {
            //Register Succeeded
            QMessageBox msgBox;
            msgBox.setText("Registration successful. You will be logged in.");
            msgBox.exec();


            this->username = username;
            write_login_to_file(username,password);

            ui->loggedInStatus->setText(std::string("Logged in as: ").append(username).c_str());
            check_lobby(sessionid);
            return;
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Error");

            ui->textEdit->setText(readBuffer.c_str());
            std::cout << readBuffer.c_str() << std::endl;
            msgBox.exec();
        }
    }
}


void MainOnlineWindow::on_logoutButton_clicked()
{
    get_host_info_from_file();

    CURL *curl = curl_easy_init();

    std::string readBuffer;
    char curl_errbuf[CURL_ERROR_SIZE];
    int err;
    curl_easy_setopt(curl, CURLOPT_URL, std::string("https://").append(host).append("/accounts/logout/").c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");



    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    err = curl_easy_perform(curl);

    //std::cout << "docbuf: " << readBuffer.size() << std::endl;


    curl_easy_cleanup(curl);
    sessionid = "";
    ui->loggedInStatus->setText(std::string("Not logged in").c_str());

    check_lobby(sessionid);

    ui->logoutButton->hide();

    ui->pushButton_2->setEnabled(true);
    ui->pushButton_2->show();
    ui->pushButton_3->setEnabled(false);
    ui->refreshLobbyButton->setEnabled(false);
    ui->joinGameButton->setEnabled(false);

}

