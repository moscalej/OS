//
// Created by alejandro on 6/21/2017.
//

#include "PageDirectoryEntry.h"

int PageDirectoryEntry::get_frame_number(int full_address) {
    int PageTableEntry= bits_to_take(12,10,full_address);
    _PTE[PageTableEntry].get_page_address();
    return 0;
}

PageDirectoryEntry::PageDirectoryEntry() {
    for (int i=0; i<1024; i++)
    {
        _PTE[i]=PageTableEntry();
    }

}

void PageDirectoryEntry::set_frame_number(int full_address, int new_frame_number) {
    int PageTableEntry= bits_to_take(12,10,full_address);
    _PTE[PageTableEntry].set_page_address(new_frame_number);
}

bool PageDirectoryEntry::is_valid(int full_adr) {
    int PageTableEntry= bits_to_take(12,10,full_adr);
    return _PTE[PageTableEntry].is_valid();

}

void PageDirectoryEntry::set_valid(int full_adr, bool valid) {
    int PageTableEntry= bits_to_take(12,10,full_adr);
    _PTE[PageTableEntry].set_valid(valid);
    return;

}
