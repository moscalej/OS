//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_DATA_BASE_ACCOUNTS_H
#define HW2_DATA_BASE_ACCOUNTS_H

#include "Account.h"
#include "Bank.h"

#include <pthread.h>
#include <map>


//i dont know if we need copy constrctor because we dont have any pointers on Account may be for the password?
class AccountDataBase {
    friend class Bank;
public:

    AccountDataBase();
    bool insert_account(int account_id, string password, int initial_ammount);
    Account * search_account(int account_id);
    bool delete_account(int account_id);


private:

    vector<Account *> get_accounts();

    pthread_rwlock_t rwlock;
    std::map<int,Account*> _Accounts;
    std::map<int,Account*>::iterator it;
};


#endif //HW2_DATA_BASE_ACCOUNTS_H
