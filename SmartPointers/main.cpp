//
//  main.cpp
//  SmartPointers
//
//  Created by Artur Hebda on 13/06/2011.
//  Copyright 2011 AdTaily. All rights reserved.
//

#include <iostream>
#include <time.h>
#include "bst.h"
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    BST<int> bst(rand()); // you can pass root value also as an argument in constructor :)
    
    for (int count = 1; count < 10000; count++) {
        int recently_added = rand();
        bst.insert(recently_added);

        if (count % 2 == 0) {
            bst.remove(recently_added);
        }
    }

    bst.in_order();
    bst.clear();
}