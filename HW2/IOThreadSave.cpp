//
// Created by alejandro on 5/26/2017.
//

#include <cstdio>
#include "IOThreadSave.h"

void IOThreadSave::save_to_log(printMsg msg, int atm_num, int id, string password, int amount, int source_balance,
                               int target_balance) {
    //newAccount, accountExists, doesntExist, badPassword, success_deposit, insufficient, success_withdraw, balance, success_transfer
    switch (msg)
    {
        case newAccount :
            logText << atm_id << ": New account id is " << atm_id << " with password " << pass << " and initial balance " << balance << endl;
            break;
        case accountExists :
            logText << atm_id << ": Your transaction failed - account with same id exists" << endl;
            break;
        case doesntExist:
            logText << atm_id << ": Your transaction failed - account id " << accountNum <<  " does not exist" << endl;
            break;
        case badPassword :
            logText << atm_id << ": Your transaction failed - password for " << accountNum << " is incorrect" << endl;
            break;
        case success_deposit:
            logText << atm_id << ": Account " << accountNum << " new balance is " << balance << " after " << amount << " was deposited" << endl;
            break;
        case insufficient:
            logText << atm_id << ": Your transaction failed - account id " << accountNum << " balance is lower than "<<amount << endl;
            break;
        case success_withdraw:
            logText << atm_id << ": Account " << accountNum << " new balance is " << balance << " after " << amount << " was withdrew" << endl;
            break;
        case balance:
            logText << atm_id << ": Account " << accountNum << " balance is " << balance << endl;
            break;
        case success_transfer:
            logText << atm_id << ": Transfer " << amount << " from account " << accountNum << " to account " << accountDest << " new account balance is " << balance
                    << " new target account balance is " << balanceDest << endl;
            break;
    pthread_mutex_unlock(&(this->mutex_log));
}

IOThreadSave::IOThreadSave(string path_to_print)   {
    _path_to_print=path_to_print;
    FILE * pfile = fopen(path_to_print.c_str(), "w+");
    fclose(pfile);
    mutex_log = PTHREAD_MUTEX_INITIALIZER;
}


IOThreadSave::~IOThreadSave() {
    pthread_mutex_destroy(&(this->mutex_log));

}
