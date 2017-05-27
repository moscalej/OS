//
// Created by alejandro on 5/27/2017.
//

#ifndef HW2_ARGS_H
#define HW2_ARGS_H

#include "Atm.h"
#include "IOThreadSave.h"
#include "Bank.h"

class Args {
public:
    Args(AccountDataBase *accountDataBase, IOThreadSave *ioThreadSave, char *text, int Atm_number) : accountDataBase(
            accountDataBase),
                                                                                                     ioThreadSave(
                                                                                                             ioThreadSave),
                                                                                                     text(text),
                                                                                                     Atm_number(
                                                                                                             Atm_number) {}

    Args() {}

    int Atm_number;
    AccountDataBase *accountDataBase;
    IOThreadSave *ioThreadSave;
    char *text;

};

void *atm_thread(void *arg) {
    Args *temp = (Args *) arg;
    string path_file = string(temp->text);

    printf((char *) arg);
    //(*temp->Atm_number)++;
    Atm ATM(temp->Atm_number, temp->accountDataBase, temp->ioThreadSave);
    ATM.do_commands(path_file);
    pthread_exit(NULL);
}

void *bank_thread(void *args) {
    Args *temp = (Args *) args;
    Bank bank1(0, "0000", 0, temp->accountDataBase, temp->ioThreadSave);
    bank1.bank_run();
    pthread_exit(NULL);
}




#endif //HW2_ARGS_H
