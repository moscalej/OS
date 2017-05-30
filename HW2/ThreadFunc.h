//
// This document was create it by
//  Alejandro Moscoso and Yonathan Haimovich
//  for the Hw 2 of Operating systems 2017 spring
//

#ifndef HW2_ARGS_H
#define HW2_ARGS_H

#include "Atm.h"


/**
 * Class Args
 * This Class is the medium we pass the arguments to the thread functions (we could have use strut be
 * we thougth that using an object will be easy) the elements of the object are
 *  int Atm_number                      : The number of the atm running on the thread
 *  AccountDataBase *accountDataBase    : A pointer to the Common data base
 *  IOThreadSave * ioThreadSave         : A pointer to the Input and Output manager
 *  char *text;                         : A string (not real string type) to the path of the atm instructions
 *  pthread_rwlock_t * finish_thread;   : A pointer to the lock to end running the print function and the charge one
 *  bool * finish_bool;                 : A bool that will action the thread finish of function and the charge
 */
class Args {
public:
    Args(AccountDataBase *accountDataBase, IOThreadSave *ioThreadSave, char *text, int Atm_number,
             pthread_rwlock_t *finish_lock, int *finish_bool);

    Args() {}

    int Atm_number;
    AccountDataBase *accountDataBase;
    IOThreadSave * ioThreadSave;
    char *text;
    pthread_rwlock_t * finish_thread;
    int * finish_bool;

};


/**
 * #Bank Print#
 * This is the function that will be pass to the Thread in charge of doing the printing to
 * the normal output "cout<<" this function will check the state of each account and will
 * print an update of the state every 0.5 sec
 * @param arg - Class Args -Relevant to this function
 *  AccountDataBase *accountDataBase    : A pointer to the Common data base
 *  IOThreadSave * ioThreadSave         : A pointer to the Input and Output manager
 *  pthread_rwlock_t * finish_thread;   : A pointer to the lock to end running the print function and the charge one
 *  bool * finish_bool;                 : A bool that will action the thread finish of function and the charge
 */
void * bank_print(void * arg);

/**
 * #Bank Charge
 * This is the function that will be pass to the Thread in charge of Charging interest
 * (an Interest will between 2% and 3%) to the accounts on the AccountDataBase(ADB).
 * and this charge will be made every 3 sec
 * @param arg - Class Args - Relevant to this function
 *  AccountDataBase *accountDataBase    : A pointer to the Common data base
 *  IOThreadSave * ioThreadSave         : A pointer to the Input and Output manager
 *  pthread_rwlock_t * finish_thread;   : A pointer to the lock to end running the print function and the charge one
 *  bool * finish_bool;                 : A bool that will action the thread finish of function and the charge
 */
void * bank_charge(void * arg);

/**
 * This is the function that will be pass to the Thread in charge of building a new Atm
 * object and run it until that object finish all the instructions writen on the instructions file(path)
 *
 * @param arg Class Args - Relevant to this function
 *  int Atm_number                      : The number of the atm running on the thread
 *  AccountDataBase *accountDataBase    : A pointer to the Common data base
 *  IOThreadSave * ioThreadSave         : A pointer to the Input and Output manager
 *  char *text;                         : A string (not real string type) to the path of the atm instructions
 */
void *atm_thread(void *arg) ;

#endif //HW2_ARGS_H
