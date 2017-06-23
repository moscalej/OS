#include "SwapDevice.h"
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

}
