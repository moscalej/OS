//
// Created by alejandro on 6/21/2017.
//

#ifndef HW3_PAGETABLE_H
#define HW3_PAGETABLE_H

#pragma once

#include <map>
#include "PageDirectoryEntry.h"
#include "PageTableEntry.h"
#include "PageDirectoryEntry.h"
#include "SwapDevice.h"
#include <queue>
using namespace std;

class VirtualMemory; //You will probably want to include this in PageTable.cpp
class PageTable
{
public:

    PageTable();

//Your Constructor (and Destructor if you need one) should go here
    int* GetPage (unsigned int adr);

private:
    queue<int*> freeFramesList; //move this to PT

    SwapDevice * swapDevice;

    map<int,int> lastUse;

    std::map<unsigned , PageDirectoryEntry > _PDE;


};

#endif //HW3_PAGETABLE_H
