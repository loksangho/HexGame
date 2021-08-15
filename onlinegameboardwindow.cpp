#include "onlinegameboardwindow.h"
#include "ui_onlinegameboardwindow.h"
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <QFile>
#include <QMessageBox>
#include "websocket_endpoint.h"
#include "connection_metadata.h"


#include "customdialog.h"




OnlineGameBoardWindow::OnlineGameBoardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OnlineGameBoardWindow())
{
    ui->setupUi(this);

    createHexagonalButtons(length,50,100,100);
    set_enable_buttons(false);

    //std::cout << "length: " << hex_button_vector.size() << std::endl;

}

void OnlineGameBoardWindow::createHexagonalButtons(int length, int size, int x_offset, int y_offset) {

    double length_of_hexagon_side = (size*sin(30*M_PI/180))/sin(120*M_PI/180);
    double move_up = sqrt(pow(length_of_hexagon_side,2)-pow(size/2,2));
    double move_right = size/2;


    QImage alpha_mask = QImage(":/images/hexagon_alpha.png").scaled(size,size,Qt::KeepAspectRatio);
    alpha_mask.fill(Qt::transparent);

    for(int j=0; j<length;j++) {
        for(int i=0; i< length; i++) {
            int var = j*length+i;
            HexButton* hex_btn = new HexButton(ui->boardWidget);
            connect(
                    hex_btn, &QPushButton::clicked,
                    this  , [var,this]{ on_HexagonalButton_clicked(var); }
            );

            hex_btn->setVisible(true);
            hex_btn->setFixedSize(QSize(size,size));

            QPixmap mask = QPixmap::fromImage(alpha_mask);
            hex_btn->setMask(mask.mask());
            hex_btn->setGeometry(i*size+j*convertToInt(move_right)+x_offset,j*size-j*convertToInt(move_up)+y_offset,size,size);

            hex_button_vector.append(hex_btn);

        }
    }


}

void OnlineGameBoardWindow::get_host_info_from_file() {
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

void OnlineGameBoardWindow::on_HexagonalButton_clicked(int val) {

    if(this->turn != player_colour) {
        return;
    }


    get_host_info_from_file();

    if(board->is_legal(val % board->get_length(), val / board->get_length(), player_colour)) {

        board->make_move(val % board->get_length(), val / board->get_length(), player_colour);
        std::string data = "{\"action\": \"claim_square\", \"user\":\"";
        data = data.append(this->username).append("\"").append(", \"game_id\":").append(std::to_string(this->gameid)).append(", \"square_id\" : ").append(std::to_string(val)).append("}");


        std::string ret_msg;
        connect_web_socket_with_text("/ws/play_board/", data, &ret_msg);





        update_board(ret_msg);
        wait_for_turn();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Illegal move, please try again.");
        msgBox.exec();
    }



}

void OnlineGameBoardWindow::update_board(std::string ret_msg) {



    boost::json::value val_ret = boost::json::parse( ret_msg );
    boost::json::object v = val_ret.as_object();
    boost::json::array squares_array = v["squares"].as_array();



    for(boost::json::value square : squares_array) {
        boost::json::object square_obj = square.as_object();

        boost::json::string status = square_obj["status"].as_string();
        boost::json::string owner = square_obj["owner_str"].as_string();
        int row = square_obj["row"].as_int64();
        int col = square_obj["col"].as_int64();

        int board_value = col + length*row;
        //TODO: draw on board

        Colour colour = Colour::EMPTY;

        std::string other = username == creator? opponent: creator;
        if(std::string(status.c_str()).compare("Selected") == 0){
            if (std::string(owner.c_str()).compare(username) == 0){
                colour = player_colour;

            }
            else if(std::string(owner.c_str()).compare(other) == 0) {
                colour = switch_turn(player_colour);
            }


        }
        else {// string is null
            colour = Colour::EMPTY;
        }
        Colour local_board_colour = board->get_colour(board_value);
        if(local_board_colour != colour) {
            board->make_move(col, row, switch_turn(player_colour));
        }



        set_button_colour(board_value, colour);


    }


    std::string other = username == creator? opponent: creator;
    if(!v["game"].as_object()["winner"].is_null()) {
        if(std::string(v["game"].as_object()["winner"].as_object()["username"].as_string().c_str()).compare(username) == 0) {
            set_enable_buttons(false);
            QMessageBox msgBox;
            msgBox.setText("You win!");
            msgBox.exec();
            perform_timer->stop();
        }
        else if(std::string(v["game"].as_object()["winner"].as_object()["username"].as_string().c_str()).compare(other) == 0) {
            set_enable_buttons(false);
            QMessageBox msgBox;
            msgBox.setText("You lose.");
            msgBox.exec();
            perform_timer->stop();
        }
    }
}

void OnlineGameBoardWindow::set_colour_turn(Colour c) {
    if(c == Colour::BLUE)
        centralWidget()->setStyleSheet("HexButton:hover{border-image:url(\":/images/hexagon_blue.png\");}");
    else
        centralWidget()->setStyleSheet("HexButton:hover{border-image:url(\":/images/hexagon_red.png\");}");
}

void OnlineGameBoardWindow::show_players() {

    std::string creator_str = creator;
    std::string opponent_str = opponent;
    if(this->creator == this->username) {
        creator_str = creator_str.append(" (You)");
    }
    else {
        opponent_str = opponent_str.append(" (You)");
    }
    ui->creatorLabel->setText(creator_str.c_str());
    ui->opponentLabel->setText(opponent_str.c_str());
}

OnlineGameBoardWindow::~OnlineGameBoardWindow()
{
    delete ui;
}

void OnlineGameBoardWindow::on_readyBbutton_clicked()
{
    ui->readyBbutton->setEnabled(false);

    get_host_info_from_file();

    std::string data = "{\"action\": \"ready\", \"user\":\"";
    data = data.append(this->username).append("\"").append(", \"game_id\":").append(std::to_string(this->gameid)).append("}");

    std::string ret_msg;
    connect_web_socket_with_text("/ws/play/", data, &ret_msg);


    boost::json::value val = boost::json::parse( ret_msg );
    boost::json::object v = val.as_object();
    boost::json::string state = v["state"].as_string();
    if(state.compare("still waiting") == 0) {
        //do nothing
        QTimer::singleShot(0, this, SLOT(perform()));
    }
    else if(state.compare("ready to start") == 0) {
        ready_to_start(v);
    }


}

void OnlineGameBoardWindow::ready_to_start(boost::json::object v) {
    //std::cout << "ready to begin" << std::endl;
    std::string choosing_user = std::string(v["choosing_user"].as_string().c_str());
    if(choosing_user.compare(username) == 0) {
        // The current player gets to choose the colour

        int colour = 0;
        bool colour_checked = false;
        CustomDialog d("Choose your colour", this);                            // We want our custom dialog called "Registration".
        d.addLabel    ("The server has determined that you can choose the colour this time. Please choose your colour below (Blue starts first) ...");           // The first element is just a text label (non interactive).
        d.addRadioGrp ("Colour: ", "Blue|Red", &colour, "Blue starts first, Red starts second", "Blue colour|Red colour", false, &colour_checked);

        d.exec();


        bool cancel_game = false;


        //std::cout << "d.exec()" << std::endl;
        if(d.wasCancelled()){                // If the user hit cancel, your values stay the same
            // quit game
        }
        else {
            std::string ret_msg2;
            if(colour==0) {
                // blue
                connect_web_socket_with_text("/ws/play/", std::string("{\"action\" : \"choose_colour\", \"colour\" : \"Blue\", \"user\": \"").append(username).append("\", \"game_id\" : ").append(std::to_string(this->gameid)).append("}"), &ret_msg2);
            }
            else {
                //red
                connect_web_socket_with_text("/ws/play/", std::string("{\"action\" : \"choose_colour\", \"colour\" : \"Red\", \"user\": \"").append(username).append("\", \"game_id\" : ").append(std::to_string(this->gameid)).append("}"), &ret_msg2);
            }

            boost::json::value val = boost::json::parse( ret_msg2 );
            boost::json::object v = val.as_object();
            boost::json::string state = v["state"].as_string();
            if(state.compare("game_starts") == 0) {

                std::string other = this->username == this->creator? this->opponent: this->creator;
                if(v["starting_user"].as_string().compare(this->username)==0) { // if current player is the starting user
                    // Self starts
                    start_game();
                    set_enable_buttons(true);

                    set_colour_turn(Colour::BLUE);
                    player_colour = Colour::BLUE;

                }
                else if (v["starting_user"].as_string().compare(other)==0) { // if current player is not starting user
                    // Other player starts
                    start_game();
                    set_enable_buttons(false);
                    set_colour_turn(Colour::RED);
                    player_colour = Colour::RED;
                    wait_for_turn();
                }
                else {
                    // something went wrong

                    std::cout << "something went wrong" << std::endl;

                }

                //std::cout << "Started Game" << std::endl;
            }
        }
    }
    else {
        // not choosing user

        check_colour();

    }
}

void OnlineGameBoardWindow::check_colour(){

    QTimer::singleShot(0, this, SLOT(perform_check_colour()));

}

void OnlineGameBoardWindow::perform_check_colour() {
    perform_timer = new QTimer(this);
    connect(perform_timer, SIGNAL(timeout()), this, SLOT(timeout_check_colour()));
    perform_timer->start(5000); // number of milliseconds between checks

}
void OnlineGameBoardWindow::timeout_check_colour() {
    std::string ret_msg3;
    connect_web_socket_with_text("/ws/play/", std::string("{\"action\" : \"get_colour\", \"game_id\" : ").append(std::to_string(this->gameid)).append("}"), &ret_msg3);
    boost::json::value val = boost::json::parse( ret_msg3 );
    boost::json::object v = val.as_object();
    boost::json::string state = v["state"].as_string();

    //std::cout << "check colour: " << state << std::endl;

    if(state.compare("colour_not_ready") == 0) {

    }
    else if(state.compare("colour_ready") == 0) {
        perform_timer->stop();
        std::string blue_user = std::string(v["blue_user"].as_string().c_str());
        std::string other = username == creator? opponent : creator;
        if(blue_user.compare(username) == 0) {
            // player begins

            start_game();
            set_enable_buttons(true);

            set_colour_turn(Colour::BLUE);
            player_colour = Colour::BLUE;

        }
        else if(blue_user.compare(other) == 0) {
            start_game();
            set_enable_buttons(false);
            set_colour_turn(Colour::RED);
            player_colour = Colour::RED;
            wait_for_turn();
        }
    }
}

void OnlineGameBoardWindow::wait_for_turn() {
    set_enable_buttons(false);
    QTimer::singleShot(0, this, SLOT(perform_check_turn()));

}

void OnlineGameBoardWindow::perform_check_turn(){
    perform_timer = new QTimer(this);
    connect(perform_timer, SIGNAL(timeout()), this, SLOT(timeout_check_turn()));
    perform_timer->start(5000); // number of milliseconds between checks
}
void OnlineGameBoardWindow::timeout_check_turn(){
    std::string ret_msg;

    std::string data = std::string("{\"action\": \"check_turn\" , ").append(" \"game_id\":").append(std::to_string(this->gameid)).append("}");


    connect_web_socket_with_text("/ws/play_board/", data, &ret_msg);

    boost::json::value val_ret = boost::json::parse( ret_msg );
    boost::json::object v = val_ret.as_object();
    boost::json::object current_turn = v["game"].as_object()["current_turn"].as_object();




    if(std::string(current_turn["username"].as_string().c_str()).compare(username) == 0) {
        //player's turn
        perform_timer->stop();
        update_board(ret_msg);
        turn = player_colour;
        set_colour_turn(player_colour);
        set_enable_buttons(true);
    }
    else {
        turn = switch_turn(player_colour);
    }

}

void OnlineGameBoardWindow::perform() {
    perform_timer = new QTimer(this);
    connect(perform_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    perform_timer->start(5000); // number of milliseconds between checks
}

void OnlineGameBoardWindow::timeout() {
    //std::cout << "Timeout" << std::endl;
    // Check if other player have joined
    std::string ret_msg;

    std::string data = "{\"action\": \"ready\", \"user\":\"";
    data = data.append(this->username).append("\"").append(", \"game_id\":").append(std::to_string(this->gameid)).append("}");

    connect_web_socket_with_text("/ws/play/", data, &ret_msg);

    boost::json::value val = boost::json::parse( ret_msg );
    boost::json::object v = val.as_object();
    boost::json::string state = v["state"].as_string();
    if(std::string(state.c_str()).compare("still waiting") == 0) {
        //do nothing

    }
    else if(state.compare("ready to start") == 0) {
        perform_timer->stop();
        ready_to_start(v);
    }



}

void OnlineGameBoardWindow::cancel() {

    perform_timer->stop();

}
void OnlineGameBoardWindow::connect_web_socket_with_text(std::string path, std::string text, std::string* ret_msg) {

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
