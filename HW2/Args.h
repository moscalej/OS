//
// Created by alejandro on 5/27/2017.
//

#ifndef HW2_ARGS_H
#define HW2_ARGS_H

#include "Atm.h"
#include "Bank.h"

class Args {
public:
    Args(AccountDataBase *accountDataBase, IOThreadSave *ioThreadSave, char *text, int Atm_number) ;

    Args() {}

    int Atm_number;
    AccountDataBase *accountDataBase;
    IOThreadSave *ioThreadSave;
    char *text;

};

void * bank_print(void * arg);

void * bank_charge(void * arg);

void *atm_thread(void *arg) ;






#endif //HW2_ARGS_H
