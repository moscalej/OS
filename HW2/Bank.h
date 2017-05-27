//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_BANK_H
#define HW2_BANK_H


#include "AccountDataBase.h"

class Bank {
public:
    //TODO: finish the run function
    //TODO: finish the print function, only format the output
    Bank(int id, string password, int initial_amount, AccountDataBase *ADB, IOThreadSave *IOTS);

    /**
     * This method will make the banck run and perform his task
     * acordig to the parameters give on the homework
     */
    void bank_run();
    void bank_close();


private:
    void charge_commission();
    vector<Account *> get_accounts();
    void print();
    int _balance;
    AccountDataBase * _ADT;
    std::map<int,Account*>::iterator it;
    float _commission_rate;

    pthread_rwlock_t mutex1;

    bool close;
    IOThreadSave *_IOTS;
};


#endif //HW2_BANK_H
