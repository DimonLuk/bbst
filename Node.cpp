#include "BBST.h"

Node::Node(int data, Node *left, Node *right) {
    _data = new int();
    *_data = data;
    _left = left;
    _right = right;
}
Node::Node(int data, int left, int right) {
    *_data = data;
    _left = new Node(left, nullptr, nullptr);
    _right = new Node(right, nullptr, nullptr);
}

Node::Node() {
    _data = new int();
}
Node::~Node() {
    delete _data;
    _data = nullptr;

    /*delete _left;
    _left = nullptr;

    delete _right;
    _right = nullptr;*/
}

Node* Node::left() const {
    return _left;
}

void Node::left(int data) {
    _left = new Node(data, nullptr, nullptr);
}

void Node::left(Node *data) {
    _left = data;
}
 
Node* Node::right() const {
    return _right;
}

void Node::right(int data) {
    _right = new Node(data, nullptr, nullptr);
}

void Node::right(Node *data) {
    _right = data;
}

int Node::data() const {
    return *_data;
}

int Node::data(int d) {
    *_data = d;
}