//
// Created by alejandro on 5/26/2017.
//

#include <cstdio>
#include "IOThreadSave.h"

void IOThreadSave::save_to_log(printMsg msg, int atm_num, int id, string password, int amount, int balance,
                               int target_id, int target_balance) {
    //newAccount, accountExists, doesntExist, badPassword, success_deposit, insufficient, success_withdraw, success_balance, success_close, success_transfer
    pthread_mutex_lock(&(this->mutex_log));
    switch (msg) {
        case newAccount :
            logFile << atm_num << ": New account id is " << id << " with password " << password
                    << " and initial balance " << amount << endl;
            break;
        case accountExists :
            logFile <<"Error "<< atm_num << ": Your transaction failed - account with same id exists" << endl;
            break;
        case doesntExist:
            logFile <<"Error " <<atm_num << ": Your transaction failed - account id " << id << " does not exist" << endl;
            break;
        case badPassword :
            logFile <<"Error " <<atm_num << ": Your transaction failed - password for " << id << " is incorrect" << endl;
            break;
        case success_deposit:
            logFile << atm_num << ": Account " << id << " new balance is " << balance << " after " << amount
                    << " was deposited" << endl;
            break;
        case insufficient:
            logFile <<"Error " <<atm_num << ": Your transaction failed - account id " << id << " balance is lower than " << amount
                    << endl;
            break;
        case success_withdraw:
            logFile << atm_num << ": Account " << id << " new balance is " << balance << " after " << amount
                    << " was withdrew" << endl;
            break;
        case success_balance:
            logFile << atm_num << ": Account " << id << " balance is " << balance << endl;
            break;
        case success_close:
            logFile << atm_num << ": Account " << id << " is now closed. balance was" << balance << endl;
            break;
        case success_transfer:
            logFile << atm_num << ": Transfer " << amount << " from account " << id << " to account " << target_id
                    << " new account balance is " << balance
                    << " new target account balance is " << target_balance << endl;
            break;
    }
            pthread_mutex_unlock(&(this->mutex_log));

}


IOThreadSave::~IOThreadSave() {

    pthread_mutex_destroy(&(mutex_log));
    logFile.close();

}

IOThreadSave::IOThreadSave(){
    logFile.open("../log.txt");
    pthread_mutex_init(&mutex_log , NULL);

}

void IOThreadSave::Bank_to_Log(float interest_rate, int amount_to_charge, int account_id) {
    pthread_mutex_lock(&(this->mutex_log));
    logFile<< "Bank: commissions of " << int(interest_rate * 100) << " % were charged, the bank gained " << amount_to_charge << " from account " << account_id << endl;
    pthread_mutex_unlock(&(this->mutex_log));
}


