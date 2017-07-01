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

    /** Constructor
     * On the constructor we create a new page table and concected to the pointer on the class
     * we do this to not have problems of memory
     * we will delete this on the destructor
     */
    VirtualMemory();

    virtual ~VirtualMemory();

    /** OurMalloc
     * We create an object with the relevant information of the virtual memory pointer (this) the size of the object
     * and the limits it can reach (the bounds of the pointer, we didn't set and error handler to handle the out of
     * memory bound problems but the base is there )
     *
     * @param size the size of the malloc on number of 4 bytes (integer used for the Vectors and Matrix)
     *              real size on bytes = size * 4
     * @return OurPointer object
     */
    OurPointer OurMalloc(size_t size);

    /**Get pointer
     * This method returns a ponter to the int indicate by the address (its a int so the addres can only has a minimun
     * offset of 4 bytes)
     * the address is build from frame_pointer(from Page Table) + offset
     *
     * @param full_virtual_address - Virtual Address
     * @return  pointer to the specific byte (for integer)
     */
    int &get_pointer(unsigned int full_virtual_address);

private:
   PageTable * pageTable;
    size_t allocated;
};
#endif //HW3_VIRTUALMEMORY_H
