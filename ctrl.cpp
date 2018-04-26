#include <iostream>
#include "BBST.h"


using namespace std;


int main() {
    Tree *tree = new Tree();
    //tree->addItem(7);
    /*tree->addItem(1);
    tree->print();
    tree->addItem(2);
    tree->print();
    tree->addItem(3);
    tree->print();
    tree->addItem(4);
    tree->print();
    tree->addItem(5);
    tree->print();
    tree->addItem(6);
    tree->print();
    tree->addItem(7);
    tree->print();
    tree->addItem(8);
    tree->print();
    tree->addItem(9);
    tree->print();
    tree->addItem(10);
    tree->print();
    tree->addItem(11);
    tree->print();
    tree->addItem(12);
    tree->print();
    tree->addItem(13);
    tree->print();
    tree->addItem(14);
    tree->print();
    tree->addItem(15);
    tree->print();*/
    tree->addItem(1);
    tree->addItem(2);
    tree->addItem(3);
    tree->addItem(4);
    tree->addItem(5);
    tree->addItem(6);
    tree->addItem(7);
    tree->print();

    Tree *anotherTree =  new Tree();
    anotherTree->addItem(8);
    anotherTree->addItem(9);
    anotherTree->print();
    cout <<  tree->contains(anotherTree);
    return 0;
}