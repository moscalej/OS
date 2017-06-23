//
// Created by alejandro on 6/20/2017.
//

#ifndef HW3_VIRTUALMEMORY_H
#define HW3_VIRTUALMEMORY_H

#pragma once
#include <queue>
#include "OurPointer.h"
#include "PageTable.h"
#define PAGESIZE 4096
#define VIRTMEMSIZE 4294967296
#define NUMOFFRAMES 64
using namespace std;
class VirtualMemory {

public:

    /*Initialize freeFramesList to contain all 64 frame
    pointers as given by PhysMem Class, initialize the PageTable, give the
    pageTable a pointer to this object so it can utilize GetFreeFrame and
    ReleaseFrame

     builds the fisical memory
     builds the Page Table
     builds swap divice(with pointer of fisical) gives pointer to Page Table
     */
    VirtualMemory();

    ~VirtualMemory();





    /*Remove one item from the freeFrameList and
    return it – suggestion, use memset(framePtr, 0, PAGESIZE) before return,
    might help debugging!
    */
    void ReleaseFrame(int* framePointer);

    /*releases the frame pointed by
    the framePointer, make sure you only use this function with a pointer to the
    beginning of the Frame! it should be the same pointer as held in the PTE.
    */
    OurPointer OurMalloc(size_t size);


    void ReleaseVirtual(unsigned int address, unsigned int address_end);

    int &get_pointer(unsigned int full_virtual_address);

private:

    PageTable pageTable;


    /*The number of ints already allocated, ((allocated *4) = (number of bytes already allocated)), this can also be used as the next
        address to be allocated.
        */
    size_t allocated;
};
#endif //HW3_VIRTUALMEMORY_H
