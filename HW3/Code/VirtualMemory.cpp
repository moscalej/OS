//
// Created by alejandro on 6/20/2017.
//

#include "VirtualMemory.h"

VirtualMemory::VirtualMemory() {}

int *VirtualMemory::GetPage(unsigned int adr) {
    return pageTable.GetPage(adr);

}
