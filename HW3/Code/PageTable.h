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
#include <fstream>

using namespace std;


class PageTable
{
public:
    /**
     * The constructor builds all the 1024 Page directory entry
     *
     *
     * @param swapDevice
     */
    PageTable(){};
    PageTable(SwapDevice *swapDevice);

    /**
     * This Method will give to the virtual memory the frame that it needs
     * from the fisical memory
     * @param adr
     * @return The frame Number
     */
    int * GetPage(unsigned int full_VA);

private:


    SwapDevice * swapDevice_;

    map<int*,int> lastUse;
    ofstream logFile;
    PageDirectoryEntry  _PDE[1024];


};



#endif //HW3_PAGETABLE_H
