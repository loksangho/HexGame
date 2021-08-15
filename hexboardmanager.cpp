#include "hexboardmanager.h"
#include <QImage>
#include <QPushButton>
#include <QObject>


unsigned int board_length = 11;

HexBoardManager::HexBoardManager() {

}

void HexBoardManager::set_button_colour(int button_index, Colour c) {
    if(c == Colour::BLUE) {
        hex_button_vector[button_index]->setStyleSheet("border-image:url(\":/images/hexagon_blue.png\");}");
    }
    else if(c == Colour::RED) {
        hex_button_vector[button_index]->setStyleSheet("border-image:url(\":/images/hexagon_red.png\");}");
    }
    else {
        hex_button_vector[button_index]->setStyleSheet("");
    }
}


void HexBoardManager::start_game() {

    board = new HexBoard(board_length);

    for(int i=0; i<hex_button_vector.size(); i++) {
        set_button_colour(i, Colour::EMPTY);
    }

}

void HexBoardManager::end_game() {

    if(board) {
        delete board;
    }

}

Colour HexBoardManager::switch_turn(Colour c) {
    if(c == Colour::BLUE) {
        return Colour::RED;
    }
    else if(c == Colour::RED) {
        return Colour::BLUE;
    }
    return c;
}

void  HexBoardManager::set_enable_buttons(bool b) {
    for(int i=0; i<hex_button_vector.size(); i++) {
        hex_button_vector[i]->setEnabled(b);
    }
}

// Converts from double to int
int HexBoardManager::convertToInt(double d) {
   d = d + 0.5 - (d<0);
   return (int)d;

}

