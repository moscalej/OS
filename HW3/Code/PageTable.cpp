//
// Created by alejandro on 6/21/2017.
//

#include "PageTable.h"

int PageTable::GetPage(unsigned int adr) {
    //check if the valid on the rigth pagedirectory (translate the addres)
    /*
     * if valid return the frame to the virtual memory
     * of not ask swap to add and update the page directory table and returns the frame
     * also unvalidate last use of frame number: find virtual adddress on map last used, set to
     * unvalid, save new VA in map
     *
     */




}

PageTable::PageTable(SwapDevice *swapDevice) : swapDevice(swapDevice) {


}

PageTable::PageTable() {
    for (int i = 0; i < 1024; ++i) {


    }
}
