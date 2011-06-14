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

struct Engine {
    string imei;
    int pistons;
    double capacity;
    Engine(const int &pistons, const double &capacity, const string &imei) : pistons(pistons), capacity(capacity), imei(imei) {}
    ~Engine() { cout << "destructor!" << endl; }
};

void nothing_at_all(Engine *engine) {
    SmartPointer<Engine> ptr(engine);
    SmartPointer<Engine> ptr_copy(ptr);

    if (ptr.is_null())
        cout << "null" << endl;
    else
        cout << "not null" << endl;

    cout << "references: " << ptr_copy.use_count() << endl;
    cout << "from pointer[imei]: " << ptr->imei << endl;
    cout << "from copied_pointer[imei]: " << (*ptr_copy).imei << endl;
}

int main (int argc, const char * argv[])
{
    Engine *engine = new Engine(6, 2401.07, "1234567890");
    nothing_at_all(engine);
    return 0;
}