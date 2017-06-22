//
// Created by alejandro on 6/21/2017.
//

#ifndef HW3_PAGEDIRECTORYENTRY_H
#define HW3_PAGEDIRECTORYENTRY_H

#include <map>
#include "PageTableEntry.h"


class PageDirectoryEntry {


public:



private:

    std::map<unsigned , PageTableEntry> PTE;

};


#endif //HW3_PAGEDIRECTORYENTRY_H
