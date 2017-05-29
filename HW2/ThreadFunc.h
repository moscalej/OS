//
// Created by alejandro on 5/27/2017.
//

#ifndef HW2_ARGS_H
#define HW2_ARGS_H

#include "Atm.h"


/**
 * Class Args
 * This Class is the medium we pass the arguments to the thread functions (we could have use strut be
 * we thougth that using an object will be easy) the elements of the object are
 *  int Atm_number : The number of the atm running on the thread
 *  AccountDataBase *accountDataBase    : A pointer to the Common data base
 *  IOThreadSave * ioThreadSave         : A pointer to the Input and Output manager
 *  char *text;                         : A string (not real string type) to the path of the atm instructions
 *  pthread_rwlock_t * finish_thread;   : A pointer to the lock to end running the print function and the charge one
 *   bool * finish_bool;                : A bool that will action the thread finish of function and the charge
 */
class Args {
public:
    Args(AccountDataBase *accountDataBase, IOThreadSave *ioThreadSave, char *text, int Atm_number,
             pthread_rwlock_t *finish_lock, bool *finish_bool);

    Args() {}

    int Atm_number;
    AccountDataBase *accountDataBase;
    IOThreadSave * ioThreadSave;
    char *text;
    pthread_rwlock_t * finish_thread;
    bool * finish_bool;

};


/**
 * #Bank Print#
 * This is the function that will be pass to the Thread in charge of doing the printing to
 * the normal output "cout<<" this funtion will check the state of each account and will
 * update the state every 0.5 sec
 * @param arg - Class Args
 */
void * bank_print(void * arg);

void * bank_charge(void * arg);

void *atm_thread(void *arg) ;






#endif //HW2_ARGS_H
