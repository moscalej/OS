//
// Created by alejandro on 6/20/2017.
//

#include "VirtualMemory.h"



VirtualMemory::VirtualMemory() {

}

int *VirtualMemory::GetPage(unsigned int adr) {
    return NULL;

}

OurPointer VirtualMemory::OurMalloc(size_t size) {
    //allocates a pointer, we added the code for your convenience
        if (allocated + size >= (VIRTMEMSIZE >> 2)) {
            throw "We are limited to 4294967296 bytes with our 32 bit address size";
        }
        OurPointer ptr(allocated, this);
        allocated += size;
        return ptr;

}

void VirtualMemory::ReleaseVirtual(unsigned int address, unsigned int address_end) {

}

int &VirtualMemory::get_pointer(unsigned int full_virtual_address) {
    int * page = this->pageTable.GetPage(full_virtual_address);
    return this->pageTable.GetPage(full_virtual_address) +( alf= (int*)bits_to_take(0,12,full_virtual_address)) ;
}
