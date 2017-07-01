//
// Created by alejandro on 6/21/2017.
//

#ifndef HW3_PAGETABLE_H
#define HW3_PAGETABLE_H

#pragma once

#include <map>
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
     */
    PageTable();

    /**
     * This Method will give to the virtual memory the frame pointer from the corresponding page.
     * will also validate/un-validate new/old page, update address if doesn't exist in page
     * @param adr -full address converted to int
     * @return The frame pointer
     */
    int * GetPage(unsigned int full_VA);

private:

    /**Print
     * This method is used to print to the log file
     * @param VA - Virtual Address
     * @param PA  - Physical Address
     * @param page_fault - if there was a page fault
     * @param exist_in_SD  - if the virtual frame exist on the Disk ( swap device for us)
     * @param evicted  - if we evict a frame(replace the content of the frame) from the physical memory
     * @param allocated_PTE
     */
    void print(int VA, int *PA, bool page_fault, int exist_in_SD, int evicted, bool allocated_PTE);

    SwapDevice * swapDevice_; //Pointer to the swap device
    map<int*,int> lastUse; //Stl for keeping track of the frames use
    ofstream logFile; // For output management
    PageDirectoryEntry  _PDE[1024];


};



#endif //HW3_PAGETABLE_H
