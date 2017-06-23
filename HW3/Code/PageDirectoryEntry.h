//
// Created by alejandro on 6/21/2017.
//

#ifndef HW3_PAGEDIRECTORYENTRY_H
#define HW3_PAGEDIRECTORYENTRY_H

#include <map>
#include "PageTableEntry.h"


class PageDirectoryEntry {


public:

    int get_frame_number(int full_address); //Pointer to beginning of frame
    void set_frame_number(int full_address, int new_frame_number); //Set the pointer to a frame
    bool is_valid(int full_adr); //Returns whether the entry is valid
    void set_valid(bool valid); //Allows to set whether the entry is valid



private:


    std::map<unsigned int , PageTableEntry> PTE;

};


#endif //HW3_PAGEDIRECTORYENTRY_H
