#ifndef BST_H
#define BST_H
//
//  bst.h
//  SmartPointers
//
//  Created by Artur Hebda on 20/06/2011.
//  Copyright 2011 AdTaily. All rights reserved.
//

#include <iostream>
#include "smart_pointer.h"
using namespace std;

// INTERFACE

// See: http://en.wikipedia.org/wiki/Binary_search_tree
template <typename T> // let's assume for a while that T is a simple type.
class BST {
private:
    class Node { // It's here because this is going to be used only inside the BST class. 
    public:
        SmartPointer<T> element;
        SmartPointer<Node> left, right, parent;

        SmartPointer<Node> min(); // returns a pointer to child of given node with minimal element.
        SmartPointer<Node> max(); // returns a pointer to child of given node with maximal element.
        SmartPointer<Node> successor(); // returns a pointer to successor (next node in in-order method) of given node.
        T & val() { return *element; } // returns as value object of node instead of pointer to it.
        bool operator==(const Node &other);
        bool operator!=(const Node &other);

        Node()
        : element(NULL), left(NULL), right(NULL), parent(NULL) {};
        Node(SmartPointer<Node> &parent)
        : element(NULL), left(NULL), right(NULL), parent(parent) {};
        Node(SmartPointer<Node> &left, SmartPointer<Node> &right)
        : element(NULL), left(left), right(right) {};
        Node(const T &new_element)
        : left(NULL), right(NULL), parent(NULL), element(new T(new_element)) {};
        Node(const T &new_element, SmartPointer<Node> &parent)
        : left(NULL), right(NULL), parent(parent), element(new T(new_element)) {};
        Node(const T &new_element, SmartPointer<Node> &left, SmartPointer<Node> &right)
        : left(left), right(right), parent(NULL), element(new T(new_element)) {};
    };
    
    SmartPointer<Node> private_root;
    
public:
    Node root() const { return *private_root; }; // from outside it's impossible to change root of bst.
    
    SmartPointer<Node> search(const T &searched_element);
    bool insert(const T &new_element);
    bool remove(const T &old_element);
    bool member(const T &element);
    void print(const T &searched_element);
    void print(const SmartPointer<Node> &node);
    void print(); // prints state of root
    void in_order(SmartPointer<Node> &node);
    void in_order();
    void post_order(SmartPointer<Node> &node);
    void post_order();
    
    friend T & Node::val(); // to hide whole logic.
    
    BST() : private_root(NULL) {};
    BST(const T &root) : private_root(new Node(root)) {};
};

// IMPLEMENTATION

template <typename T>
bool BST<T>::insert(const T &new_element) {
    SmartPointer<Node> new_node(new Node(new_element));
    SmartPointer<Node> destination(private_root);
    SmartPointer<Node> destination_parent(NULL);

    if (private_root.is_null())
        private_root = new_node;
    
    else {
        while (! destination.is_null() ) {
            destination_parent = destination;

            if ( new_node->val() < destination->val() )
                destination = destination->left;
            else
                destination = destination->right;
        }

        new_node->parent = destination_parent;

        if ( new_node->val() < destination_parent->val() )
            destination_parent->left = new_node;
        else
            destination_parent->right = new_node;
    }
    
    return true;
}

template <typename T>
bool BST<T>::remove(const T &old_element) {
    SmartPointer<Node> delete_node = search(old_element); // node to remove
    SmartPointer<Node> delete_parent(NULL); // parent of the removing node
    SmartPointer<Node> replacing_node(NULL); // node which will replace removing node
    SmartPointer<Node> replacing_node_max(NULL);
    
    if (! delete_node.is_null() ) {
        delete_parent = delete_node->parent;
        
        if (delete_node->left.is_null() || delete_node->right.is_null() ) { // has at most one child.
            if (! delete_node->left.is_null() ) // has left child.
                replacing_node = delete_node->left;
            else
                replacing_node = delete_node->right;
        }
        else { // has both children.
            replacing_node = delete_node->successor(); // guarantee that this node has not left child.
            replacing_node_max = replacing_node->max(); // guarantee that this node has not right child.
            
            replacing_node->left = delete_node->left;
            delete_node->left->parent = replacing_node;
            
            if (replacing_node_max != replacing_node) {
                replacing_node_max->right = delete_node->right;
                delete_node->right->parent = replacing_node_max;
            }
        }
        
        if (! delete_parent.is_null() ) {
            if (delete_parent->left == delete_node)
                delete_parent->left = replacing_node;
            else
                delete_parent->right = replacing_node;
        }
        else // removing node is root!
            private_root = replacing_node;
        
        if (! replacing_node.is_null() )
            replacing_node->parent = delete_parent;
        
        return true;
    }
    else
        return false;
}

template <typename T>
bool BST<T>::member(const T &element) {
    return (! search(element).is_null() );
}

template <typename T>
void BST<T>::print(const T &searched_element) {
    print( search(searched_element) );
}

template <typename T>
void BST<T>::print() {
    print( private_root );
}

template <typename T>
void BST<T>::print(const SmartPointer<Node> &node) {
    if (! node.is_null() ) {
        cout << "current: " << node->val() << endl;
        if (! node->left.is_null() )
            cout << "left: " << node->left->val() << endl;
        if (! node->right.is_null() )
            cout << "right: " << node->right->val() << endl;
    }
    else
        cout << "current: NULL" << endl;
}

template <typename T>
void BST<T>::in_order() {
    in_order(private_root);
}

template <typename T>
void BST<T>::in_order(SmartPointer<Node> &node) {
    if (! node.is_null() ) {
        if (! node->left.is_null() ) in_order(node->left);
        cout << node -> val() << endl;
        if (! node->right.is_null() ) in_order(node->right);
    }
}

template <typename T>
void BST<T>::post_order() {
    post_order(private_root);
}

template <typename T>
void BST<T>::post_order(SmartPointer<Node> &node) {
    if (! node.is_null() ) {
        if (! node->left.is_null() ) post_order(node->left);
        if (! node->right.is_null() ) post_order(node->right);
        cout << node->val() << endl;
    }
}

template <typename T>
bool BST<T>::Node::operator==(const Node &other) {
    return (element == other.element);
}

template <typename T>
bool BST<T>::Node::operator!=(const Node &other) {
    return (element != other.element);
}

template <typename T>
SmartPointer<typename BST<T>::Node> BST<T>::search(const T &searched_element) {
    SmartPointer<Node> current(private_root);
    
    while (! current.is_null() && current->val() != searched_element ) {
        if ( current->val() > searched_element )
            current = current->left;
        else
            current = current->right;
    }
    
    if (! current.is_null() && current->val() == searched_element )
        return current;
    else
        return NULL;
}

template <typename T>
SmartPointer<typename BST<T>::Node> BST<T>::Node::min() {
    SmartPointer<Node> current(this);
    
    if (! current.is_null() ) {  
        while (! current->left.is_null() )
            current = current->left;
    }
    
    return current;
}

template <typename T>
SmartPointer<typename BST<T>::Node> BST<T>::Node::max() {
    SmartPointer<Node> current(this);
    
    if (! current.is_null() ) {
        while (! current->right.is_null() )
            current = current->right;
    }
    
    return current;
}

template <typename T>
SmartPointer<typename BST<T>::Node> BST<T>::Node::successor() {
    SmartPointer<Node> current(this);
    SmartPointer<Node> that(this);
    
    if (! current->right.is_null() )
        return current->right->min();
    
    current = current->parent;
    
    while (! current.is_null() && current->left != that) {
        that = current;
        current = current->parent;
    }
    
    return current;
}

#endif