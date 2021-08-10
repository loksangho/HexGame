#include "graph.h"


Graph::Graph() {

}

Graph::~Graph() {

}

int Graph::get_length() {return length;}

QVector<Colour> Graph::get_node_values() { return node_values; }

void Graph::set_node_values(QVector<Colour> node_values) {this->node_values = node_values;} // for testing purposes only


// Sets the colour of the graph at location 'x'
void Graph::set_colour(int x, Colour c) {
    node_values[x] = c;
}

// returns the number of vertices in the graph
int Graph::vertex_count() {
    return graph.size();
}

// returns the number of edges in the graph
int Graph::edge_count() {
    int count = 0;
    for(int i=0; i< graph.size(); i++) {
        QVector<bool> row = graph[i];
        for (int j=0; j < row.size(); j++) {
            if (i >= j) {
                bool val = row[j];
                if(val == true) {
                    count++;
                }
            }
        }
    }
    return count;
}

Graph::Graph(int length) : graph(length*length, QVector<bool>(length*length)), node_values(QVector<Colour>(length*length, Colour::EMPTY)) {}

// tests whether there is an edge from node x to node y.
bool Graph::adjacent(int x, int y) {
    return graph[x][y];
}

// lists all nodes y such that there is an edge from x to y.
QVector<int> Graph::neighbours(int x) {
    QVector<bool> row = graph[x];
    QVector<int> nodes_y;
    for(int i=0; i< row.size(); i++) {
        if(row[i]) {
            nodes_y.push_back(i);
        }
    }
    return nodes_y;
}

// adds to G the edge from x to y, if it is not there.
void Graph::add_edge(int x, int y) {
    graph[x][y] = true;
}

// removes the edge from x to y, if it is there.
void Graph::delete_edge(int x, int y) {
    graph[x][y] = false;
}

// returns the value associated with the node x.
Colour Graph::get_node_value(int x) {
    return node_values[x];
}

// initialises the length of graph
void Graph::initialise_length(int length) {
    this->length = length;
    graph = QVector<QVector<bool> > (length*length, QVector<bool>(length*length));
    node_values = QVector<Colour>(length*length);
}
