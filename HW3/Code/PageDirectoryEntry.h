//
// Created by alejandro on 6/21/2017.
//

#ifndef HW3_PAGEDIRECTORYENTRY_H
#define HW3_PAGEDIRECTORYENTRY_H

#include <map>
#include "PageTableEntry.h"
#include "HelpFunc.h"


class PageDirectoryEntry {


public:
    PageDirectoryEntry();
    int * get_address(int full_VA); //Pointer to beginning of frame
    void set_address(int full_VA, int *new_address); //Set the pointer to a frame
    bool is_valid(int full_VA); //Returns whether the entry is valid
    void set_valid(int full_VA, bool valid); //Allows to set whether the entry is valid



private:


    PageTableEntry _PTE[1024];
};


#endif //HW3_PAGEDIRECTORYENTRY_H
