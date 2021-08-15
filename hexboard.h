#pragma once

#ifndef HEXBOARD_H
#define HEXBOARD_H

/*
 *  This is the HexBoard class which provides functionality for playing the game.
 *
 */

#include "graph.h"
#include <QPair>
#include <QString>
#include <iostream>


class HexBoard {
    public:
        HexBoard(int length);
        ~HexBoard();
        bool is_top_acute_corner(int x);
        bool is_top_obtuse_corner(int x);
        bool is_bottom_acute_corner(int x);
        bool is_bottom_obtuse_corner(int x);
        bool is_top_boundary(int x);
        bool is_bottom_boundary(int x);
        bool is_left_boundary(int x);
        bool is_right_boundary(int x);
        bool is_middle(int x);
        void place_colour(int i, int j, Colour c);
        bool is_legal(int i, int j, Colour c);
        bool is_next_to(int i, int j, Colour c, Colour other);
        bool on_valid_boundary(int i, int j, Colour c);
        int get_length();
        Colour get_colour(int x);
        Colour get_colour_trial(int x);
        Colour has_winner(bool trial);
        void check_adjacent(int x, Colour c, QVector<int> visited, bool& winner, bool trial);
        bool check_blue_path_exists_trial(int node);
        void insert_unique(QVector<int>& vec, int x);
        bool  contains(QVector<int>vec, int x);
        QVector<Node>::iterator contains_id(QVector<Node>& vec, int x);
        QVector<Node>::iterator contains_value(QVector<Node>& vec, int val);
        int make_move(int i, int j, Colour c);
        void check_node(QVector<Node>& unvisited,int x);
        void reset_game();
        int best_move_AI(Colour AI_colour, int num_of_MC_trials);
        int convert_location_to_index(int i, int j);
        QString winner_string(Colour winner);
        QPair<int,int> convert_index_to_location(int x, int length);
        friend std::ostream& operator<<(std::ostream& os, HexBoard& board);
    private:
        void make_trial_node_vec();
        int num_of_moves_made = 0;
        int length;
        Graph* board_graph;
        QVector<Colour> trial_nodes;
};

#endif // HEXBOARD_H
