//
// Created by alejandro on 6/20/2017.
//

#ifndef HW3_OURPOINTER_H
#define HW3_OURPOINTER_H






class  VirtualMemory;
class OurPointer {
public:
    /**Constructor
     * will construct a pointer with a virtual mememory and size (to know if we have segmentation foult (a little extra)
     * @param adr - The number of the first byte of the virtual memory (this number can change)
     * @param address_end  - The max address that this pointer can reach
     * @param vrtlMem  - Pointer to the virtual Memory handler
     */
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
