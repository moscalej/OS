//
// Created by alejandro on 6/21/2017.
//

#ifndef HW3_PAGETABLE_H
#define HW3_PAGETABLE_H


#pragma once
#include “PageDirectoryEntry.h”
class VirtualMemory; //You will probably want to include this in PageTable.cpp
class PageTable
{
public:
//Your Constructor (and Destructor if you need one) should go here
    int* GetPage (unsigned int adr);
private:
//Fill the class with the necessary member variables
};

#endif //HW3_PAGETABLE_H
