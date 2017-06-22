//
// Created by alejandro on 6/21/2017.
//

#ifndef HW3_PAGETABLEENTRY_H
#define HW3_PAGETABLEENTRY_H


#pragma once
class PageTableEntry
{
public:
//Your Constructor (and Destructor if you need one) should go here
    int* get_page_address(); //Pointer to beginning of frame
    void set_page_address(int* adr); //Set the pointer to a frame
    bool is_valid(); //Returns whether the entry is valid
    void set_valid(bool valid); //Allows to set whether the entry is valid
private:
    int* address_;
    bool valid_;
};


#endif //HW3_PAGETABLEENTRY_H
