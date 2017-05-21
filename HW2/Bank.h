//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_BANK_H
#define HW2_BANK_H
#include "Account.h"

class Bank {
public:
    Bank(int id,string password,int initial_amount);

    /**
     * This method will make the banck run and perform his task
     * acordig to the parameters give on the homework
     */
    void bank_run();

private:
    void charge_comission();
    void print();
    int _account_id;
    string _password;
    int _balance;

};


#endif //HW2_BANK_H
