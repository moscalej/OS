#include <unordered_map>
#include <stdlib.h>

#include <string.h>
#include <iostream>
#include <queue>

#include "PhysMem.h"

class SwapDevice {
    friend class PageTable;
public:
    SwapDevice();

    int *write_this_page_to_the_frame(unsigned virtual_address, int &exist_swap_dive, int &evicted_page);

private:
    void WriteFrameToSwapDevice(int pageNumber, int * page_out); //Write the content of page to the swap device, "pageOut" is the frame base pointer where the page is now allocated
    int ReadFrameFromSwapDevice(int pageNumber, int* pageIn); //Put the content of the page in "page". " pageIn " is the frame base pointer to where the page is about to be allocated, returns -1 if page is not stored in the swap device.
    std::unordered_map<int, int*> _data;
    std::queue< std::pair<int,int> > freeFramesList;
    size_t _size;
    int start_counter = 64;
    int* first_frame_;
};
