//
// Created by alejandro on 6/20/2017.
//

#ifndef HW3_VIRTUALMEMORY_H
#define HW3_VIRTUALMEMORY_H
#pragma once
#include <queue>
#include "PageTable.h"
#include "OurPointer.h"

#define VIRTMEMSIZE 4294967296


using namespace std;
class Ourpointer;
class VirtualMemory {

public:

    /**
     *
     */
    VirtualMemory();

    virtual ~VirtualMemory();

    OurPointer OurMalloc(size_t size);

    int &get_pointer(unsigned int full_virtual_address);

private:
   PageTable * pageTable;
    size_t allocated;
};
#endif //HW3_VIRTUALMEMORY_H
