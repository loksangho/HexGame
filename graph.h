#pragma once

#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <iostream>
#include "node.h"


class Graph {
    public:
        Graph();
        Graph(int length);
        //Graph(Graph& G);
        ~Graph();
        void initialise_length(int length);
        int get_length();
        int vertex_count();
        int edge_count();
        bool adjacent(int x, int y);
        QVector<int> neighbours(int x);
        void add_edge(int x, int y);
        void delete_edge(int x, int y);
        Colour get_node_value(int x);
        void set_colour(int x, Colour c);
        QVector<Colour> get_node_values();
        void set_node_values(QVector<Colour> node_values); // for testing purposes only


    private:
        int length;
        QVector<QVector<bool> > graph;
        QVector<Colour> node_values;
};


#endif // GRAPH_H
