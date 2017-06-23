#include "SwapDevice.h"
#include "HelpFunc.h"

#define FRAMESZ 4096

using namespace std;

void SwapDevice::WriteFrameToSwapDevice(int pageNumber, int* pageOut) {
    if (_data[pageNumber] == NULL) {
        if (++_size > 104857) {
            cerr << "The swap device seems to be using too much space, worth investigating" << endl;
        }
        _data[pageNumber] = (int*)malloc(FRAMESZ);
    }
    memcpy(_data[pageNumber], pageOut, FRAMESZ);
}

int SwapDevice::ReadFrameFromSwapDevice(int pageNumber, int* pageIn) {
    if (_data[pageNumber] == NULL) {
        return -1;
    }
    memcpy(pageIn, _data[pageNumber], FRAMESZ);
    return 0;
}

SwapDevice::SwapDevice(PhysMem *PM) : PM(PM) {
    /*
     * We only fill the queue with 64 values that will rotate the number of frames
     */
    for (int i = 0; i < 64; ++i) {
       this->freeFramesList.push(std::make_pair(i,i));
    }

}

int * SwapDevice::write_this_page_to_the_frame(unsigned virtual_address) {
    /*
     * get VM, pop frame_number from queue, swap physical memory, return frame_number,
     * push back to queue
     * we will work here only with pages number for that we need to change the values to page numbers from virtual address
     *
     */


    int old_page_number = this->freeFramesList.front().first;
    int frame_number = this->freeFramesList.front().second;

    int page_number = bits_to_take(12,22,virtual_address);
    int * frame_pointer = this->PM->GetFrame(frame_number);

    this->WriteFrameToSwapDevice(old_page_number, frame_pointer);
    int result= this->ReadFrameFromSwapDevice(page_number,frame_pointer);
    this->freeFramesList.pop();
    std::pair<int,int> temp = std::make_pair(page_number,frame_number);
    this->freeFramesList.push(temp);

    return (result==0)?frame_pointer:NULL;


}
