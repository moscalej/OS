//
// Created by alejandro on 6/10/2017.
//

#ifndef HW4_HELPFUNC_H
#define HW4_HELPFUNC_H
#pragma once
#include <cmath>
#include <iostream>


/** Bits to take
 * this function will transform a int Address to [Msb.. [A[number_bits]..lsb] ..Lsb] and then make a
 * an int from a subset of the address
 * @param lsb - the bit number that indicates the least significant bit of the new addres
 * @param number_of_bits
 * @param address
 * @return
 */
int bits_to_take(int lsb, int number_of_bits, int address);




#endif //HW4_HELPFUNC_H
