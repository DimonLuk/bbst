#ifndef BBST_H
#define BBST_H
class Node {
    private:
        Node *_left;
        Node *_right;
        int *_data;
    public:
        Node();
        ~Node();
        Node(int data, Node *left, Node *rigth);
        Node(int data, int left, int right);
        Node* left() const;
        Node* right() const;
        void left(int data);
        void right(int data);
        void left(Node *data);
        void right(Node *data);
        int data() const;
        int data(int d);
};

class Tree {
    private:
        Node *_root;
        void _addItem(Node *root, int *data, bool *flag);
        void _search(Node *root, int *data, bool *flag) const;
        void _print(Node *root) const;
        void _deleteItem(Node *root, Node *parent, int *data, int *result, bool *isLeftSubtree);
        void _makeEmpty(Node *root, Node *parent);
        void _retreive(Node *root, int *data, int *result) const;
        int _height(Node *root) const;
        void _reBalance(Node *root);
        int _childCount(Node *root) const;
    public:
        bool isEmpty() const;
        bool isFull() const;
        void makeEmpty();
        void print() const;
        bool search(int item) const;
        int retreive(int item) const;
        int deleteItem(int item);
        bool addItem(int item);
        int height() const;
        bool contains(Tree *tree) const;
        Tree();
        ~Tree();

};
#endif