 //
// Created by alejandro on 6/21/2017.
//

#include "PageTable.h"
#include "HelpFunc.h"

int PageTable::GetPage(unsigned int full_adr) {
    //check if the valid on the rigth pagedirectory (translate the addres)
    /*
     * if valid return the frame to the virtual memory
     * of not ask swap to add and update the page directory table and returns the frame
     * also unvalidate last use of frame number: find virtual adddress on map last used, set to
     * unvalid, save new VA in map
     *
     */
    int PageDirEntry= bits_to_take(22,10,full_adr);
    if (this->_PDE[PageDirEntry].is_valid(full_adr))
    {
        return this->_PDE[PageDirEntry].get_frame_number(full_adr);
    }
    int new_frame_number=swapDevice->write_this_page_to_the_frame(full_adr);
    int old_VA=this->lastUse[new_frame_number];
    this->lastUse[new_frame_number]=full_adr;
    this->set_valid(old_VA,false);
    this->_PDE[PageDirEntry].set_frame_number(full_adr, new_frame_number);
    this->set_valid(full_adr,true);
    return new_frame_number;

}

PageTable::PageTable(SwapDevice *swapDevice) : swapDevice(swapDevice) {


}

PageTable::PageTable() {
    for (int i = 0; i < 1024; ++i) {


    }
}
