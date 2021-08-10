#include "onlinegameboardwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainonlinewindow.h"
#include <QPushButton>
#include <math.h>
#include <iostream>
#include <QFile>
#include "customdialog.h"
#include <QPainter>
#include "mywidget.h"
#include "boardview3d.h"
#include <QSurfaceFormat>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow())
{

        ui->setupUi(this);
        //setupStyleSheet();
        createHexagonalButtons(length,50,100,100);
        set_enable_buttons(false);

    //centralWidget()->setStyleSheet("HexButton:hover{border-image:url(\":/images/hexagon_blue.png\");}");
}

void MainWindow::setup_object() {

}

MainWindow::~MainWindow()
{
    destroy_thread_manager();
    delete ui;

}

void MainWindow::setupStyleSheet() {

    QFile File(":/qss/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    setStyleSheet(StyleSheet);
}




void MainWindow::createHexagonalButtons(int length, int size, int x_offset, int y_offset) {
/*
    double height_of_edge_bar = 40;
    QPoint top_edge[4] = {QPoint(-size/2,-size/2), QPoint(-size/2-height_of_edge_bar, -size/2-height_of_edge_bar), QPoint((length-1)*size+size/2+height_of_edge_bar,-size/2-height_of_edge_bar), QPoint((length-1)*size+size/2,-size/2)};
    QPainter painter(this);
    painter.setBrush(Qt::cyan);
    painter.setPen(Qt::darkCyan);
    painter.drawConvexPolygon(top_edge, 4);
    painter.drawRect(0, 0, 100,100);
*/
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
            //hex_btn->setStyleSheet("border-image:url(\":/images/hexagon.png\");background-color: transparent;background-repeat: none;   border: none;");
            QPixmap mask = QPixmap::fromImage(alpha_mask);
            hex_btn->setMask(mask.mask());
            hex_btn->setGeometry(i*size+j*convertToInt(move_right)+x_offset,j*size-j*convertToInt(move_up)+y_offset,size,size);

            hex_button_vector.append(hex_btn);

        }
    }


}


void MainWindow::computer_move() {
    set_enable_buttons(false);

    if(ui) {
        ui->lineEdit->setText("Computer is thinking...");
    }
    //int move_int = board->best_move_AI(switch_turn(player_colour), 1000);
    setup_thread_manager();
    emit operate(QString(), board, player_colour, mc_trials);
}

void MainWindow::on_HexagonalButton_clicked(int val) {
    //ui->lineEdit->setText(QString::number(val));
    //HexButton * b = qobject_cast<HexButton *>(sender());
    QPair<int,int> move = board->convert_index_to_location(val, board->get_length());
    if(board->is_legal(move.first,move.second,player_colour)) {
        set_button_colour(val,player_colour);
        board->make_move(move.first,move.second,player_colour);



        std::cout << *board << std::endl;
        Colour winner = board->has_winner(false);
        if(winner != Colour::EMPTY) {

            if(player_colour == winner) {
               QMessageBox msg_box(this);
               msg_box.setInformativeText("You Win!");
               msg_box.exec();
               end_game();
            }
            else {
                QMessageBox msg_box(this);
                msg_box.setInformativeText("You Lose!");
                msg_box.exec();
                end_game();
            }

            ui->startGameButton->setEnabled(true);

        }
        else {
           turn = switch_turn(turn);
           computer_move();
        }

    }
}

void MainWindow::on_startGameButton_clicked()
{
    std::string  name = "First Last";            // NOTE: these lines of code (the variables you wish to change)
    int colour = 0;
    bool colour_checked = true;
    int difficulty = 0;
    bool difficulty_checked = true;

    CustomDialog d("Choose your colour", this);                            // We want our custom dialog called "Registration".
    d.addLabel    ("Please choose your colour below (Blue starts first) ...");           // The first element is just a text label (non interactive).
    d.addLineEdit ("name:  ", &name, "No middle name!");
    d.addRadioGrp ("Colour: ", "Blue|Red", &colour, "Blue starts first, Red starts second", "Blue colour|Red colour", false, &colour_checked);
    d.addLabel    ("Please choose your difficulty (Easy is fastest) ...");           // The first element is just a text label (non interactive).
    d.addRadioGrp ("Difficulty: ", "Easy|Intermediate|Hard", &difficulty, "Based on Monte Carlo AI method", "MC trials=50|MC trials=200|MC trials=1000", false, &difficulty_checked);

    d.exec();                             // Execution stops here until user closes dialog



    if(d.wasCancelled()){                // If the user hit cancel, your values stay the same
      return;
    }                                 // and you probably don't need to do anything
    else {
        if(colour != -1) {
            player_name = QString::fromStdString(name);
            player_colour = colour==0?Colour::BLUE:Colour::RED;
            switch(difficulty){
            case 0:
                mc_trials = 50;
                break;
            case 1:
                mc_trials = 200;
                break;
            case 2:
                mc_trials = 1000;
                break;
            default:
                mc_trials= 50;
            }
            ui->startGameButton->setEnabled(false);
            turn = Colour::BLUE;
            start_game();
            set_move();
            return;
        }
    }

}



void MainWindow::set_move() {

    if(player_colour == turn) { // Player starts first
        set_enable_buttons(true);
        set_colour_turn(player_colour);
    }
    else { // Computer moves

        computer_move();

    }
}

void MainWindow::set_colour_turn(Colour c) {
    if(c == Colour::BLUE)
        centralWidget()->setStyleSheet("HexButton:hover{border-image:url(\":/images/hexagon_blue.png\");}");
    else {
        centralWidget()->setStyleSheet("HexButton:hover{border-image:url(\":/images/hexagon_red.png\");}");
    }
}




void MainWindow::setup_thread_manager() {
    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &MainWindow::handleResults);
    workerThread.start();

}

void MainWindow::destroy_thread_manager(){
    workerThread.quit();
    workerThread.wait();

}

void MainWindow::handleResults(const QString &str) {
    destroy_thread_manager();
    int move_int = str.toInt();
    //std::cout << move_int << std::endl;
    QPair<int,int> move_pair = board->convert_index_to_location(move_int, board->get_length());
    if(board->is_legal(move_pair.first, move_pair.second, switch_turn(player_colour))) {
        board->make_move(move_pair.first, move_pair.second, switch_turn(player_colour));
        set_button_colour(board->convert_location_to_index(move_pair.first, move_pair.second), switch_turn(player_colour));
        turn = switch_turn(turn);
    }
    else {
        std::cout << "AI making illegal move. Should not be here" << std::endl;
    }
    Colour winner = board->has_winner(false);
    if(winner != Colour::EMPTY) {

        if(player_colour == winner) {
           QMessageBox msg_box(this);
           msg_box.setInformativeText("You Win!");
           msg_box.exec();
        }
        else {
            QMessageBox msg_box(this);
            msg_box.setInformativeText("You Lose!");
            msg_box.exec();
        }

        ui->startGameButton->setEnabled(true);

    }
    else {
        std::cout << *board << std::endl;
        set_enable_buttons(true);
        if(ui)
            ui->lineEdit->setText("Player's turn.");
        set_colour_turn(player_colour);
    }
}


void MainWindow::on_pushButton_clicked()
{
    MainOnlineWindow* online_window = new MainOnlineWindow();
    this->close();
    online_window->show();

}


void MainWindow::on_pushButton_2_clicked()
{
    BoardView3D* board_3d = new BoardView3D(this);
    this->setVisible(false);

    board_3d->show();

    /*QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);

    Window window;
    window.setFormat(format);
    window.resize(QSize(800, 600));
    window.show();*/
}

