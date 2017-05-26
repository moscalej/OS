//
// Created by amoscoso on 5/21/2017.
//
#include <algorithm>
#include "AccountDataBase.h"

AccountDataBase::AccountDataBase() {
    rd_count=0;
    this->db_write_lock=PTHREAD_MUTEX_INITIALIZER;
    this->db_read_lock=PTHREAD_MUTEX_INITIALIZER;

}

bool AccountDataBase::insert_account(int account_id, string password, int initial_amount) {
     Account * temp = new Account(account_id,password,initial_amount);
    
        this->_Accounts[account_id]=temp;
    return false;
}

Account* AccountDataBase::search_account(int account_id) {
    Account * temp  = this->_Accounts[account_id];

    return temp;

}

bool AccountDataBase::delete_account(int account_id) {
//todo need to what hapend if the key is not on the map
//    todo also to think how will the dinamics will work for the delete
    Account * temp  = this->_Accounts[account_id];
    if (temp != NULL){
        this->_Accounts.erase(account_id);
        delete(temp);
        return true;
    }
    return false;
}

vector<Account *> AccountDataBase::get_accounts() {
    vector<Account*> temp;
    pthread_rwlock_rdlock(&(this->rwlock));
    for (this->it = this->_Accounts.begin() ;it!=_Accounts.end(); ++it) {
        temp.push_back(it->second);
    }
    pthread_rwlock_unlock(&(this->rwlock));
    return vector<Account *>();
}
