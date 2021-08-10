#include "node.h"

Node::Node(int id, int value) :id(id), value(value){ }
int Node::get_value() { return value;}
void Node::set_value(int value) { this->value = value;};
int Node::get_id() { return id;}
