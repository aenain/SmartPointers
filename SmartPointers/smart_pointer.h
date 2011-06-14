#ifndef SMART_POINTER_H
#define SMART_POINTER_H
//
//  smart_pointer.h
//  SmartPointers
//
//  Created by Artur Hebda on 13/06/2011.
//  Copyright 2011 AdTaily. All rights reserved.
//
#include <iostream>
using namespace std;

typedef int Counter;

template <class T>
class SmartPointer {
    T *_pointer;
    Counter *_counter;

    void add_reference();
    void remove_reference();
    void remove_object_if_there_are_no_references_left();
    
public:
    Counter use_count() const;
    bool is_null() const;

    T & operator*();
    T * operator->();
    T ** operator&();

    SmartPointer<T> & operator=(const SmartPointer<T> &source);
    SmartPointer(T *element) : _pointer(element), _counter(new Counter(0)) { add_reference(); }
    SmartPointer(const SmartPointer<T> &source) : _pointer(source._pointer), _counter(source._counter) { add_reference(); }
    ~SmartPointer() { remove_reference(); remove_object_if_there_are_no_references_left(); }
};

template <class T>
void SmartPointer<T>::add_reference() {
    (*_counter)++;
}

template <class T>
void SmartPointer<T>::remove_reference() {
    (*_counter)--;
}

template <class T>
void SmartPointer<T>::remove_object_if_there_are_no_references_left() {
    if (*_counter == 0) {
        delete _pointer;
    }
}

template <class T>
Counter SmartPointer<T>::use_count() const {
    return *_counter;
}

template <class T>
bool SmartPointer<T>::is_null() const {
    return (_pointer == NULL);
}

template <class T>
T & SmartPointer<T>::operator*() {
    return *_pointer;
}

template <class T>
T * SmartPointer<T>::operator->() {
    return _pointer;
}

template <class T>
T ** SmartPointer<T>::operator&() {
    return &_pointer;
}

template <class T>
SmartPointer<T> & SmartPointer<T>::operator=(const SmartPointer<T> &source) {
    _pointer = source._pointer;
    _counter = source._counter;

    add_reference();
    return *this;
}

#endif