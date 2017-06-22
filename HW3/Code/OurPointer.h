//
// Created by alejandro on 6/20/2017.
//

#ifndef HW3_OURPOINTER_H
#define HW3_OURPOINTER_H


#pragma once
#include "PageTable.h"
class OurPointer {
public:
    OurPointer(int adr, VirtualMemory* vrtlMem); //Constructor
    ~OurPointer(); //Destructor
    int& operator*(); //Overload operator*
    OurPointer& operator++(); //Overload ++operator
    OurPointer operator++(int); //Overload operator++
    OurPointer& operator--(); //Overload operator--
    OurPointer operator--(int); //Overload --operator
private:

    unsigned int _adr; //the virtual address
    VirtualMemory* _vrtlMem; //for requesting translations
};


#endif //HW3_OURPOINTER_H
