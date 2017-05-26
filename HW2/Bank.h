//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_BANK_H
#define HW2_BANK_H
#include "Account.h"
#include "AccountDataBase.h"

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
    vector<Account *> get_accounts();
    void print();
    int _account_id;
    string _password;
    int _balance;
    AccountDataBase * _ADT;
    std::map<int,Account*>::iterator it;
    float _commission_rate;
};


#endif //HW2_BANK_H
