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
    int PageDirEntry= bits_to_take(22,10,full_VA);
    bool page_valid=this->_PDE[PageDirEntry].is_valid(full_VA);
    if (page_valid)
    {
         new_phys_address= this->_PDE[PageDirEntry].get_address(full_VA);
    } else {
        new_phys_address = swapDevice_->write_this_page_to_the_frame(full_VA);
        map<int *, int>::iterator old_pair;
        old_pair = this->lastUse.find(new_phys_address);
        if (old_pair != lastUse.end()) {
            this->lastUse[new_phys_address] = full_VA;
            this->_PDE[PageDirEntry].set_valid(old_pair->second, false);
        }
        allocated_PTE=this->_PDE[PageDirEntry].set_address(full_VA, new_phys_address);
        this->_PDE[PageDirEntry].set_valid(full_VA, true);
    }
    this->print(full_VA, new_phys_address, !page_valid, swapDevice_->freeFramesList.back().first, allocated_PTE);

    return new_phys_address;

}

 PageTable::PageTable(SwapDevice *swapDevice) {
     swapDevice_=swapDevice;
     logFile.open("./log.csv");
     logFile<<"Page Number,Virtual Address,Physical Address,Page Fault,Swap,Evicted,Allocated Page Table Entries"<<endl;

     for(int i=0; i<1023; i++)
     {
         _PDE[i]=PageDirectoryEntry();
     }


 }

 void PageTable::print(int VA, int *PA, bool page_fault, int evicted, bool allocated_PTE) {
     int page_num=VA/4096;
     int* phys_adr=((PA)+bits_to_take(0,12,VA));//need to correct -offset of firs frame
     int swap=0;
     int evicted_page=-1;
     if (page_fault)
         if (PA!=NULL)
             swap=1;
             evicted_page=evicted;
     logFile<<page_num<<","<<VA<<","<<phys_adr<<","<<(int)page_fault<<","<<swap<<","<<evicted_page<<","<<(int)allocated_PTE<<endl;

 }








