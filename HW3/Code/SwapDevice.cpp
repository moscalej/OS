#include "SwapDevice.h"


#define FRAMESZ 4096

using namespace std;

void SwapDevice::WriteFrameToSwapDevice(int pageNumber, int *pageOut) {
    if (_data[pageNumber] == NULL) {
        if (++_size > 104857) {
            cerr << "The swap device seems to be using too much space, worth investigating" << endl;
        }
        _data[pageNumber] = (int *) malloc(FRAMESZ);
    }
    memcpy(_data[pageNumber], pageOut, FRAMESZ);
}

int SwapDevice::ReadFrameFromSwapDevice(int pageNumber, int *pageIn) {
    if (_data[pageNumber] == NULL) {
        return -1;
    }
    memcpy(pageIn, _data[pageNumber], FRAMESZ);
    return 0;
}

SwapDevice::SwapDevice() {

    for (int i = 0; i < 64; ++i) {
        this->pair_pageNumber_frameNumber.push(std::make_pair(i, i));
    }
    first_frame_ = PhysMem::Access().GetFrame(0);

}

int * SwapDevice::fetch_frame_from_virtual(unsigned virtual_address, int &exist_swap_dive, int &evicted_page) {



    int old_page_number = this->pair_pageNumber_frameNumber.front().first;
    int frame_number = this->pair_pageNumber_frameNumber.front().second;
    evicted_page=old_page_number;
    int page_number = bits_to_take(12, 22, virtual_address);
    int *frame_pointer = PhysMem::Access().GetFrame(frame_number);

    this->WriteFrameToSwapDevice(old_page_number, frame_pointer);
    exist_swap_dive = this->ReadFrameFromSwapDevice(page_number, frame_pointer);


    this->pair_pageNumber_frameNumber.pop();
    std::pair<int, int> temp = std::make_pair(page_number, frame_number);
    this->pair_pageNumber_frameNumber.push(temp);

    if(this->start_counter !=0){
        exist_swap_dive = -1;
        this->start_counter --;
        evicted_page=-1;
    }

    return frame_pointer ;


}
