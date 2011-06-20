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

//struct Node {
//    int key;
//    SmartPointer<Node> parent, left, right;
//    Node(const int &key = 0) : key(key), parent(NULL), left(NULL), right(NULL) {}
//};
//
//void create_tree(SmartPointer<Node> &root) {
//    SmartPointer<Node> parent = root;
//
//    for (int i = 0; i < 10; i++) {
//        Node *node = new Node(i);
//        SmartPointer<Node> current_node(node);
//
//        current_node->parent = parent;
//
//        if (i % 2 == 0) {
//            parent->left = current_node;
//            parent->right = parent->left;
//            parent->right.nullify();
//        }
//        else {
//            parent->right = current_node;
//            parent->left = parent->right;
//            parent->left.nullify();
//        }
//
//        parent = current_node;
//    }
//}
//
//void print_tree(const SmartPointer<Node> &root) { // pre-order
//    if (! root.is_null()) {
//        cout << root.use_count() << ' ' << root->key << endl;
//
//        if (! root ->left.is_null()) print_tree(root->left);
//        if (! root ->right.is_null()) print_tree(root->right);
//    }
//}
//
//int main (int argc, const char * argv[])
//{
//    SmartPointer<Node> root(new Node(50));
//    create_tree(root);
//    print_tree(root);
//    return 0;
//}

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