//
// Created by alejandro on 6/21/2017.
//

#include "PageTableEntry.h"

int * PageTableEntry::get_page_address() {
    return address_;
}

void PageTableEntry::set_page_address(int *adr) {
    address_=adr;

}

bool PageTableEntry::is_valid() {
    return valid_;
}

void PageTableEntry::set_valid(bool valid) {
    valid_=valid

}

PageTableEntry::PageTableEntry() {
    valid_=false;
}
