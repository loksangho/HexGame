#pragma once

#ifndef NODE_H
#define NODE_H

/*
 *  This is the class representing a node of the graph for the game logic.
 *
 */

#include "colour.h"

class Node {
    public:
        Node(int id=0, int value=0);
        int get_value();
        void set_value(int value);
        int get_id();

    private:
        int value;
        int id;

};



#endif // NODE_H
