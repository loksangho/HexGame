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

    std::cout << "Choose a colour: Blue (B) or Red (R). (Blue goes first):" << std::endl;
/*
    string input_colour;
    Colour player_colour;

    while (input_colour != "B" && input_colour != "R") {
        std::cin >> input_colour;
        if(input_colour.compare("B") == 0) {
            player_colour = Colour::BLUE;
            break;
        }
        else if(input_colour.compare("R") == 0) {
            player_colour = Colour::RED;
            break;
        }
        std::cout << "Please enter the letters 'R' or 'B':" << std::endl;;
    }

    if(player_colour==Colour::BLUE) {
        std::cout << "Player begins." << std::endl;
    }
    else {
        std::cout << "Computer begins." << std::endl;
    }

    Colour turn = Colour::BLUE;
    while(board.has_winner() == Colour::EMPTY) {
        if(player_colour == turn) {
            string i_str,j_str;
            int i,j;
            bool is_legal = false;

            while(!is_legal) {

                do {
                    std::cout << "Please enter valid 'i' value (horizontal value):" << std::endl;
                    std::cin >> i_str;
                    i = stoi(i_str);
                } while(i<0 || i>= board.get_length());

                do {
                    std::cout << "Please enter valid 'j' value (vertical value):" << std::endl;
                    std::cin >> j_str;
                    j = stoi(j_str);
                } while(j<0 && j>= board.get_length());

                if(board.is_legal(i,j,player_colour)) {
                    board.make_move(i,j,player_colour);
                    turn = switch_turn(turn);

                    std::cout << board << std::endl;
                    is_legal = true;
                }
                else {
                    std::cout << "Illegal move. Please try again." << std::endl;
                }

            }
        }
        else {
            int move = board.best_move_AI(switch_turn(player_colour), 1000);
            pair<int,int> move_pair = board.convert_index_to_location(move, board.get_length());
            if(board.is_legal(move_pair.first, move_pair.second, switch_turn(player_colour))) {
                board.make_move(move_pair.first, move_pair.second, switch_turn(player_colour));
                turn = switch_turn(turn);
                std::cout << board << std::endl;
            }
            else {
                std::cout << "AI making illegal move. Should not be here" << std::endl;
            }
        }
    }
    std::cout << board.winner_string(board.has_winner()) << std::endl;
*/
    return;

}
