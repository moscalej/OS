//
// Created by alejandro on 6/21/2017.
//

#include "PageDirectoryEntry.h"

int * PageDirectoryEntry::get_address(int full_VA) {
    int PageTableEntry= bits_to_take(12,10,full_VA);

    return _PTE[PageTableEntry].get_page_address();
}

PageDirectoryEntry::PageDirectoryEntry() {

    this->allocated_=false;

}

bool PageDirectoryEntry::set_address(int full_VA, int *new_address) {
    int PageTableEntry= bits_to_take(12,10,full_VA);
    _PTE[PageTableEntry].set_page_address(new_address);
    if (allocated_==false)
    {
        allocated_= true;
        return true;
    }
    return false;
}

bool PageDirectoryEntry::is_valid(int full_VA) {
    int PageTableEntry= bits_to_take(12,10,full_VA);
    return _PTE[PageTableEntry].is_valid();

}

void PageDirectoryEntry::set_valid(int full_VA, bool valid) {
    int PageTableEntry= bits_to_take(12,10,full_VA);
    _PTE[PageTableEntry].set_valid(valid);
    return;

}
