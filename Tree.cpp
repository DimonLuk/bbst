#include "BBST.h"
#include <iostream>
using namespace std;


Tree::Tree() {
    _root = nullptr;
}

bool Tree::isEmpty() const{
    if(_root == nullptr){
        return true;
    }
    return false;
}

bool Tree::isFull() const {
    Node *tmp = new Node();
    if(tmp == nullptr) {
        cout << "Tree is full" << endl;
        return true;
    }
    return false;
}

bool Tree::addItem(int item) {
    if(isFull()) return false;
    if(isEmpty()) {
        _root = new Node(item, nullptr, nullptr);
        return true;
    } else {
        bool flag = true;
        _addItem(_root, &item, &flag);
        return flag;
    }
}

void Tree::_addItem(Node *root, int *data, bool *flag) {
    if(*data < root->data() && root->left() == nullptr) {
        root->left(*data);
        *flag = true;
        _reBalance(_root);
        return;
    } else if(*data > root->data() && root->right() == nullptr) {
        root->right(*data);
        *flag = true;
        _reBalance(_root);
        return;
    } else if(*data == root->data()) {
        *flag = true;
        _reBalance(_root);
        return;
    } else if(*data < root->data() && root->left() != nullptr) {
        _addItem(root->left(), data, flag);
    } else if(*data > root->data() && root->right() != nullptr) {
        _addItem(root->right(), data, flag);
    }
}

bool Tree::search(int item) const{
    if(isEmpty()) return false;
    bool flag = false;
    _search(_root, &item, &flag);
    if(!flag) cout << "Item hasn't been found" << endl;
    return flag;
}

void Tree::_search(Node *root, int *data, bool *flag) const {
    if(*data == root->data()) {
        *flag = true;
        return;
    } else if(root == nullptr) {
        return;
    } else if(*data < root->data()) {
        _search(root->left(), data, flag);
    } else if(*data > root->data()) {
        _search(root->right(), data, flag);
    }
}

void Tree::print() const {
    cout << "\n";
    if(isEmpty()) {
        cout << "List is empty" << endl;
        return;
    }
    _print(_root);
    cout << "\n";
}

void Tree::_print(Node *root) const {
    if(root == nullptr) return;
    cout << root->data() << ", ";
    _print(root->left());
    _print(root->right());
}

int Tree::deleteItem(int item) {
    if(item == _root->data()) {
        cout << "If you want to delete the whole tree, please use makeEmpty()";
        return -1;
    }
    if(isEmpty()) {
        cout << "Tree is empty";
        return 0;
    }
    int result = -1;
    bool isLeftSubtree = false;
    if(item < _root->data()) isLeftSubtree = true;
    _deleteItem(_root, _root, &item, &result, &isLeftSubtree);
}

void Tree::_deleteItem(Node *root, Node *parent, int *data, int *result, bool *isLeftSubtree) {
    if(root == nullptr) return;
    if(*data < root->data()) _deleteItem(root->left(), root, data, result, isLeftSubtree);
    if(*data > root->data()) _deleteItem(root->right(), root, data, result, isLeftSubtree);
    if(*data == root->data()) {
        *result = root->data();
        if(root->left() == nullptr && root->right() == nullptr && parent->left() == root) {
            delete root;
            parent->left(nullptr);
            _reBalance(_root);
            return;
        }
        if(root->left() == nullptr && root->right() == nullptr && parent->right() == root) {
            delete root;
            parent->right(nullptr);
            _reBalance(_root);
            return;
        }
        if(*isLeftSubtree) {
            if(root->right() == nullptr) {
                parent->left(root->left());
                delete root;
                _reBalance(_root);
                return;
            }
            Node *theRightest = root;
            Node *theRightestParent = root;
            while(theRightest->right() != nullptr) {
                theRightestParent = theRightest;
                theRightest = theRightest->right();
            }
            root->data(theRightest->data());
            delete theRightest;
            theRightestParent->right(nullptr);
            _reBalance(_root);
            return;
        } else {
            if(root->left() == nullptr) {
                parent->right(root->right());
                delete root;
                _reBalance(_root);
                return;
            }
            Node *theLeft = root;
            Node *theLeftParent = root;
            while(theLeft->left() != nullptr) {
                theLeftParent = theLeft;
                theLeft = theLeft->left();
            }
            root->data(theLeft->data());
            delete theLeft;
            theLeftParent->left(nullptr);
            _reBalance(_root);
            return;
        }
    }
}

void Tree::makeEmpty() {
    if(isEmpty()) return;
    _makeEmpty(_root, _root);
    delete _root;
    _root = nullptr;
}

void Tree::_makeEmpty(Node *root, Node *parent) {
    if(root == nullptr) return;
    _makeEmpty(root->left(), root);
    _makeEmpty(root->right(), root);
    if(parent->left() != nullptr) delete parent->left();
    if(parent->right() != nullptr) delete parent->right();
    parent->left(nullptr);
    parent->right(nullptr);
}

int Tree::retreive(int item) const{
    if(isEmpty()) return -1;
    int result = -1;
    _retreive(_root, &item, &result);
    if(result == -1) cout << "Item hasn't been found" << endl;
    return result;
}

void Tree::_retreive(Node *root, int *data, int *result) const {
    if(*data == root->data()) {
        *result = *data;
        return;
    } else if(root == nullptr) {
        return;
    } else if(*data < root->data()) {
        _retreive(root->left(), data, result);
    } else if(*data > root->data()) {
        _retreive(root->right(), data, result);
    }
}

void Tree::_reBalance(Node *root) {
    if(root == nullptr) return;
    _reBalance(root->left());
    _reBalance(root->right());
    
    int left_ = _childCount(root->left());
    int right_ = _childCount(root->right());

    
     int balanceFactor = left_ - right_;
     /*print();
     cout << balanceFactor << "\t" << root->data() << "\n";*/
     if(balanceFactor <= -2) {
         if(root->right()->left() == nullptr) { //Left rotation
            int tmp = root->data();
            Node *tmpN = root->left();
            root->data(root->right()->data());
            root->left(tmp);
            if(tmpN != nullptr) {
                root->left()->left(tmpN);
            }
            tmpN = root->right();
            root->right(root->right()->right());
            delete tmpN;
            _reBalance(root);//Balance until we don't have perfect balance
            return;
        } else if(root->right()->left() != nullptr){//Right-left rotation
            int tmp = root->data();
            Node *tmpN = root->left();
            Node *theLeft = root->right()->left();
            Node *theLeftParent = root->right();
            while(theLeft->left() != nullptr){ //Find the smallest element
                theLeftParent = theLeft;
                theLeft = theLeft->left();
            }
            root->data(theLeft->data());
            root->left(tmp);
            if(tmpN != nullptr){
                    root->left()->left(tmpN);
            }
            delete theLeft;
            theLeftParent->left(nullptr);
            _reBalance(root);
            return;
        }
     }
     if(balanceFactor >= 2) {
        if(root->left()->right() == nullptr) { //Right rotation
            int tmp = root->data();
            Node *tmpN = root->right();
            root->data(root->left()->data());
            root->right(tmp);
            if(tmpN != nullptr) {
                root->right()->right(tmpN);
            }
            tmpN = root->left();
            root->left(root->left()->left());
            delete tmpN;
            _reBalance(root);
            return;
        } else if(root->left()->right() != nullptr){//Left-right rotation
            int tmp = root->data();
            Node *tmpN = root->right();
            Node *theLeft = root->left()->right();
            Node *theLeftParent = root->left();
            while(theLeft->right() != nullptr){ //Find the smallest element
                theLeftParent = theLeft;
                theLeft = theLeft->right();
            }
            root->data(theLeft->data());
            root->right(tmp);
            if(tmpN != nullptr){
                root->right()->right(tmpN);
            }
            delete theLeft;
            theLeftParent->right(nullptr);
            _reBalance(root);
            return;
        }
     }
     return;
}

int Tree::height() const {
    if(isEmpty()) {
        cout << "Tree is empty";
        return -1;
    }
    int result = _height(_root);
    return result;
}

int Tree::_height(Node *root) const {
    if(root == nullptr) return 0;
    return 1 + max(_height(root->left()), _height(root->right()));
}

int Tree::_childCount(Node *root) const {
    if(root == nullptr) return 0;
    return 1 + _childCount(root->left()) + _childCount(root->right());
}

Node* Tree::root() const {
    return _root;
}

bool Tree::contains(Tree *tree) const {
    bool flag = true;
    _contains(_root, tree->root(), &flag);
    return flag;
}

void Tree::_contains(Node *root, Node *anotherRoot, bool *flag) const {
    if(!*flag)
        return;
    if(root == nullptr && anotherRoot == nullptr) return;
    if(root == nullptr || anotherRoot == nullptr) {
        *flag = false;
        return;
    }
    if(anotherRoot->data() < root->data()) {
        _contains(root->left(), anotherRoot, flag);
        return;
    }
    if(anotherRoot->data() > root->data()) {
        _contains(root->right(), anotherRoot, flag);
        return;
    }
    if(anotherRoot->data() == root->data()) {
        if(anotherRoot->left() != nullptr)
            _contains(_root, anotherRoot->left(), flag);
        if(anotherRoot->right() != nullptr)
            _contains(_root, anotherRoot->right(), flag);
        return;
    }
}