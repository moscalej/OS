//
// Created by amoscoso on 5/21/2017.
//
#include <algorithm>
#include "AccountDataBase.h"

AccountDataBase::AccountDataBase() {

    this->rwlock=PTHREAD_RWLOCK_INITIALIZER;

}

bool AccountDataBase::insert_account(int account_id, string password, int initial_ammount) {
    
    pthread_rwlock_wrlock(&(this->rwlock)); //TODO: if we need copy constructor, also do delete to the
     Account * temp = new Account(account_id,password,initial_ammount);
    
    this->_Accounts[account_id]=temp;

    pthread_rwlock_unlock(&(this->rwlock));
    return false;
}

Account* AccountDataBase::search_account(int account_id) {
    pthread_rwlock_rdlock(&(this->rwlock)); //todo need to what hapend if the key is not on the map
    Account * temp  = this->_Accounts[account_id];
    pthread_rwlock_unlock(&(this->rwlock));

    return temp;

}

bool AccountDataBase::delete_account(int account_id) {

    pthread_rwlock_wrlock(&(this->rwlock)); //todo need to what hapend if the key is not on the map
//    todo also to think how will the dinamics will work for the delete
    Account * temp  = this->_Accounts[account_id];
    if (temp != NULL){
        this->_Accounts.erase(account_id);
        delete(temp);
        pthread_rwlock_unlock(&(this->rwlock));
        return true;
    }
    pthread_rwlock_unlock(&(this->rwlock));
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
