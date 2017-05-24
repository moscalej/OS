//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_DATA_BASE_ACCOUNTS_H
#define HW2_DATA_BASE_ACCOUNTS_H

#include "Account.h"
#include <vector>
#include <pthread.h>

class AccountDataBase {
    AccountDataBase();
    bool insert_account(Account *new_account);
    Account * search_account(int account_id);
    bool delete_account(int account_id);


public:
private:
    pthread_rwlock_t rwlock;
    vector<Account*> _Accounts;
};


#endif //HW2_DATA_BASE_ACCOUNTS_H
