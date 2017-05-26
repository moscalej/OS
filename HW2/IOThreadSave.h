//
// Created by alejandro on 5/26/2017.
//

#ifndef HW2_IOTHREADSAVE_H
#define HW2_IOTHREADSAVE_H

#include "Atm.h"
#include <elf.h>

class IOThreadSave {
public:
    void print_console(string to_print );
    void save_to_log( string to_write_doc);

private:
    pthread_mutex_t mutex_print;
    pthread_mutex_t mutex_log;
};


#endif //HW2_IOTHREADSAVE_H
