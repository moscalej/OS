#include <unordered_map>
#include <stdlib.h>

#include <string.h>
#include <iostream>
#include <queue>

#include "PhysMem.h"

class SwapDevice {
    friend class PageTable;
public:
    SwapDevice();// Constructor

    /** Fetch frame
     * This method will will swap a frame from the physical memory to the disc ( by the FIFO ruling of swap) and load in
     * to the memory the corresponding page to the virtual memory ( we only have one program) we don't need a CR3
     * register to check from witch process is call the swap
     *
     * @param virtual_address - virtual address of the page
     * @param exist_swap_dive - if exist on the disk ( 0 if true, -1 if false) passed by reference
     * @param evicted_page - (-1 if the page was evicted  else the number of the page evicted) passed by refence
     * @return pointer to the frame (first byte of the frame)
     */
    int *fetch_frame_from_virtual(unsigned virtual_address, int &exist_swap_dive, int &evicted_page);

private:
    void WriteFrameToSwapDevice(int pageNumber, int * page_out); //Write the content of page to the swap device, "pageOut" is the frame base pointer where the page is now allocated
    int ReadFrameFromSwapDevice(int pageNumber, int* pageIn); //Put the content of the page in "page". " pageIn " is the frame base pointer to where the page is about to be allocated, returns -1 if page is not stored in the swap device.
    std::unordered_map<int, int*> _data;
    std::queue< std::pair<int,int> > pair_pageNumber_frameNumber;
    size_t _size;
    int start_counter = 64; // use for the boot of the memory
    int* first_frame_;
};
