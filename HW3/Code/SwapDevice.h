#include <unordered_map>
#include <vector>
#include <string.h>
#include <iostream>
#include "PhysMem.h"

#define PAGESIZE 4096
class SwapDevice
{
    public:
        SwapDevice() : _size(0) {}
        void WriteFrameToSwapDevice(int pageNumber, i t); //Write the content of page to the swap device, "pageOut" is the frame base pointer where the page is now allocated
        int ReadFrameFromSwapDevice(int pageNumber, int* pageIn); //Put the content of the page in "page". " pageIn " is the frame base pointer to where the page is about to be allocated, returns -1 if page is not stored in the swap device.
    private:
        PhysMem * PM;
        std::unordered_map<int, int*> _data;
        size_t _size;   
};
