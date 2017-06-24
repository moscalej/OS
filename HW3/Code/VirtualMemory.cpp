//
// Created by alejandro on 6/20/2017.
//

#include "VirtualMemory.h"
#include "OurPointer.h"

OurPointer VirtualMemory::OurMalloc(size_t size) {
    //allocates a pointer, we added the code for your convenience
        if (allocated + size >= (VIRTMEMSIZE >> 2)) {
            throw "We are limited to 4294967296 bytes with our 32 bit address size";
        }
        OurPointer ptr((int) allocated, (int) (allocated + size), this);
        allocated += size;
        return ptr;

}


int &VirtualMemory::get_pointer(unsigned int full_virtual_address) {

    int * page = this->pageTable->GetPage(full_virtual_address);
    int offset= bits_to_take(0,12,full_virtual_address);

    return page[offset/4] ;
}

VirtualMemory::VirtualMemory() {
    PageTable * temp = new PageTable;
    this->pageTable=temp;
    this->allocated=0;
}

