 //
// Created by alejandro on 6/21/2017.
//

#include "PageTable.h"


int * PageTable::GetPage(unsigned int full_VA) {
    //check if the valid on the rigth pagedirectory (translate the addres)
    /*
     * if valid return the frame to the virtual memory
     * of not ask swap to add and update the page directory table and returns the frame
     * also unvalidate last use of frame number: find virtual adddress on map last used, set to
     * unvalid, save new VA in map
     *
     */
    int* new_phys_address=NULL;
    bool allocated_PTE=false;
    int existance_swap=0;
    int evicted_page=-1;
    int PageDirEntry= bits_to_take(22,10,full_VA);
    bool page_valid=this->_PDE[PageDirEntry].is_valid(full_VA);
    if (page_valid)
    {
         new_phys_address= this->_PDE[PageDirEntry].get_address(full_VA);

    } else {
        new_phys_address = swapDevice_->fetch_frame_from_virtual(full_VA, existance_swap, evicted_page);
        map<int *, int>::iterator old_pair;
        std::pair<int*, int> new_pair = std::make_pair(new_phys_address, full_VA);
        old_pair = this->lastUse.find(new_phys_address);
        if (old_pair != lastUse.end()) {
            this->_PDE[PageDirEntry].set_valid(old_pair->second, false);
            this->lastUse[new_phys_address] = full_VA;
        } else
        {
            this->lastUse.insert(new_pair);
        }
        allocated_PTE=this->_PDE[PageDirEntry].set_address(full_VA, new_phys_address);
        this->_PDE[PageDirEntry].set_valid(full_VA, true);
    }
    this->print(full_VA, new_phys_address, !page_valid, existance_swap, evicted_page, allocated_PTE);

    return new_phys_address;

}

 PageTable::PageTable() {

     SwapDevice * temp = new SwapDevice;
     this->swapDevice_=temp;
     logFile.open("./log.csv");
     logFile<<"Page Number,Virtual Address,Physical Address,Page Fault,Swap,Evicted,Allocated Page Table Entries"<<endl;


 }

 void PageTable::print(int VA, int *PA, bool page_fault, int exist_in_SD, int evicted, bool allocated_PTE) {
     int page_num=VA/4096;
     int* phys_adr=((PA)+bits_to_take(0,12,VA)/4);//need to correct -offset of firs frame
     int swap=0;
     uint32_t phys_adr_decimal_shifted= reinterpret_cast<uintptr_t>(phys_adr)-reinterpret_cast<uintptr_t>(swapDevice_->first_frame_);
     int evicted_page=-1;
     if (page_fault) {
         if (exist_in_SD == 0) {
             evicted_page = evicted;
             swap = 1;
         }
     }
     logFile<<page_num<<","<<VA<<","<<phys_adr_decimal_shifted<<","<<(int)page_fault<<","<<swap<<","<<evicted_page<<","<<(int)allocated_PTE<<endl;

 }










