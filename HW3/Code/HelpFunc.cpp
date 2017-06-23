//
// Created by amoscoso on 6/23/2017.
//

#include "HelpFunc.h"
int bits_to_take(int lsb, int number_of_bits, int address) {
    int temp = 0;
    int temp2 = 0;
    for (int j = 0; j < lsb; ++j) {
        address = address / 2;
    }

    for (int i = 0; i < number_of_bits; i++) {
        if (address == 0) break;
        temp2 = address % 2;
        address = address / 2;
        temp2 = temp2 * (int) pow((double) (2), (double) i);
        temp = temp + temp2;
    }
    return temp;
}