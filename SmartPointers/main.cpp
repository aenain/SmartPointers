//
//  main.cpp
//  SmartPointers
//
//  Created by Artur Hebda on 13/06/2011.
//  Copyright 2011 AdTaily. All rights reserved.
//

#include <iostream>
#include "smart_pointer.h"
using namespace std;

struct Node {
    int key;
    SmartPointer<Node> parent, left, right;
    Node(const int &key = 0) : key(key), parent(NULL), left(NULL), right(NULL) {}
};

void create_tree(SmartPointer<Node> &root) {
    SmartPointer<Node> parent = root;

    for (int i = 0; i < 10; i++) {
        Node *node = new Node(i);
        SmartPointer<Node> current_node(node);

        current_node->parent = parent;

        if (i % 2 == 0)
            parent->left = current_node;
        else
            parent->right = current_node;

        parent = current_node;
    }
}

void print_tree(const SmartPointer<Node> &root) { // pre-order
    if (! root.is_null()) {
        cout << root.use_count() << ' ' << root->key << endl;

        if (! root ->left.is_null()) print_tree(root->left);
        if (! root ->right.is_null()) print_tree(root->right);
    }
}

int main (int argc, const char * argv[])
{
    SmartPointer<Node> root(new Node(50));
    create_tree(root);
    print_tree(root);
    return 0;
}