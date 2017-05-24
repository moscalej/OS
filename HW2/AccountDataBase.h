//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_DATA_BASE_ACCOUNTS_H
#define HW2_DATA_BASE_ACCOUNTS_H

#include "Account.h"

#include <pthread.h>
#include <map>


//i dont know if we need copy constrctor because we dont have any pointers on Account may be for the password?
class AccountDataBase {
public:

    AccountDataBase();
    bool insert_account(int account_id, string password, int initial_ammount);
    Account * search_account(int account_id);
    bool delete_account(int account_id);

private:

    pthread_rwlock_t rwlock;
    std::map<int,Account*> _Accounts;
};


#endif //HW2_DATA_BASE_ACCOUNTS_H
