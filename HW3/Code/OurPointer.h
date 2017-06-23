//
// Created by alejandro on 6/20/2017.
//

#ifndef HW3_OURPOINTER_H
#define HW3_OURPOINTER_H






class  VirtualMemory;
class OurPointer {
public:
    OurPointer(int adr, int address_end, VirtualMemory *vrtlMem); //Constructor

    virtual ~OurPointer(); //Destructor
    int& operator*(); //Overload operator*
    OurPointer& operator++(); //Overload ++operator
    OurPointer operator++(int); //Overload operator++
    OurPointer& operator--(); //Overload operator--
    OurPointer operator--(int); //Overload --operator
private:

    unsigned int address_end;
    unsigned int _adr; //the virtual address
    unsigned  int address_start;
    VirtualMemory* _vrtlMem; //for requesting translations
};


#endif //HW3_OURPOINTER_H
