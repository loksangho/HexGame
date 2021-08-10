#pragma once

#ifndef NODE_H
#define NODE_H


#include "Colour.h"

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
