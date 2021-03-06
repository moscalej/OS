//
// Created by alejandro on 6/20/2017.
//

#include <iostream>
#include "OurPointer.h"
#include "VirtualMemory.h"



OurPointer::OurPointer(int adr, int address_end, VirtualMemory *vrtlMem) {
    this->_adr=(unsigned int)(adr * 4);
    this->address_start = (4 *this->_adr);
    this->_vrtlMem = vrtlMem;
    this->address_end=(unsigned int) (4 * address_end);
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

    this->_adr=this->_adr + 4;
    if(this->_adr>this->address_end){
        std::cerr<<"segmentation fault"<<std::endl;
    }
    return *this;
}

OurPointer &OurPointer::operator--() {
    this->_adr=this->_adr - 4;
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
    int & temp =this->_vrtlMem->get_pointer(this->_adr);
    return temp ;
}
