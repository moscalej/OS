//
// Created by alejandro on 6/20/2017.
//

#include "VirtualMemory.h"
#include "OurPointer.h"



VirtualMemory::VirtualMemory() {

}



OurPointer VirtualMemory::OurMalloc(size_t size) {
    //allocates a pointer, we added the code for your convenience
        if (allocated + size >= (VIRTMEMSIZE >> 2)) {
            throw "We are limited to 4294967296 bytes with our 32 bit address size";
        }
        OurPointer ptr((int)allocated, this, (int)(allocated + size));
        allocated += size;
        return ptr;

}

void VirtualMemory::ReleaseVirtual(unsigned int address, unsigned int address_end) {

}

int &VirtualMemory::get_pointer(unsigned int full_virtual_address) {
    int * page = this->pageTable.GetPage(full_virtual_address);
    int offset= bits_to_take(0,12,full_virtual_address);

    return page[offset];
}

VirtualMemory::~VirtualMemory() {

}
