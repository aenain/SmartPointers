//
//  main.cpp
//  SmartPointers
//
//  Created by Artur Hebda on 13/06/2011.
//  Copyright 2011 AdTaily. All rights reserved.
//

#include <iostream>
#include "bst.h"
using namespace std;

int main() {
    BST<int> bst(8); // you can pass root value also as an argument in constructor :)
    
    // See: http://upload.wikimedia.org/wikipedia/commons/thumb/d/da/Binary_search_tree.svg/200px-Binary_search_tree.svg.png
    //bst.insert(8); // root!
    bst.insert(3);
    bst.insert(10);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(14);
    bst.insert(7);
    bst.insert(13);
    
    bst.in_order();
}