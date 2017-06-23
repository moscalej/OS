//
// Created by alejandro on 6/20/2017.
//

#include "OurPointer.h"


OurPointer::OurPointer(int adr, VirtualMemory *vrtlMem, int address_end) {
    this->_adr=(unsigned int) adr;
    this->address_start = this->_adr;
    this->_vrtlMem = vrtlMem;
    this->address_end;
}

OurPointer::~OurPointer() {
    //many things to do
    //this->_vrtlMem->ReleaseVirtual(this->_adr, this->address_end);

}

OurPointer OurPointer::operator--(int) {

    OurPointer result(*this);   // make a copy for result
    --(*this);              // Now use the prefix version to do the work
    return result;

}

OurPointer &OurPointer::operator++() {

    this->_adr++;
    if(this->_adr>this->address_end){
        std::cerr<<"segmentation fault"<<std::endl;
    }
    return *this;
}

OurPointer &OurPointer::operator--() {
    this->_adr--;
    if(this->_adr<this->address_start){
        std::cerr<<"segmentation foult"<<std::endl;
    }
    return *this;

}

OurPointer OurPointer::operator++(int) {
    OurPointer result(*this);   // make a copy for result
    ++(*this);              // Now use the prefix version to do the work
    return result;
}

int &OurPointer::operator*() {

    return this->_vrtlMem->get_pointer(this->_adr);
}
