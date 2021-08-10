#ifndef HEXBOARDMANAGER_H
#define HEXBOARDMANAGER_H
#include "hexbutton.h"
#include "Colour.h"
#include "mywidget.h"
#include "hexboard.h"



class HexBoardManager
{

public:
    QVector<HexButton*> hex_button_vector;
    HexBoard* board;
    Colour turn = Colour::BLUE;
    HexBoardManager();
    int length =11;

    virtual void set_button_colour(int button_index, Colour c);
    void start_game();
    void end_game();

    Colour switch_turn(Colour c);

    virtual void  set_enable_buttons(bool b);

    int convertToInt(double d);

private slots:

};

#endif // HEXBOARDMANAGER_H
