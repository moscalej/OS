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


class PageTable
{
public:
    /**
     * The constructor builds all the 1024 Page directory entry
     *
     *
     * @param swapDevice
     */
    PageTable(SwapDevice *swapDevice);

    /**
     * This Method will give to the virtual memory the frame that it needs
     * from the fisical memory
     * @param adr
     * @return The frame Number
     */
    int GetPage (unsigned int full_address);

private:
    int is_valid(unsigned int full_address);
    void set_valid(unsigned int full_address, bool state);
    int swap_frame(unsigned int full_address);



    SwapDevice * swapDevice;

    map<int,int> lastUse;

    std::map<unsigned , PageDirectoryEntry > _PDE;


};

#endif //HW3_PAGETABLE_H
