#include "workflowmanager.h"
#include <iostream>


Colour WorkflowManager::switch_turn(Colour c) {
    if(c == Colour::BLUE) {
        return Colour::RED;
    }
    else if(c == Colour::RED) {
        return Colour::BLUE;
    }
    return c;
}



WorkflowManager::WorkflowManager(int length){ board = new HexBoard(11); }

void WorkflowManager::play_game() {
    std::cout << "Game of Hex" << std::endl;

    //std::cout << "Choose a colour: Blue (B) or Red (R). (Blue goes first):" << std::endl;

    return;

}
