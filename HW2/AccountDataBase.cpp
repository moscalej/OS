//
// This document was create it by
//  Alejandro Moscoso and Yonathan Haimovich
//  for the Hw 2 of Operating systems 2017 spring
//

#include "AccountDataBase.h"


AccountDataBase::AccountDataBase() {
    rd_count = 0;
    _balance = 0;
    pthread_mutex_init(&this->db_write_lock, NULL);
    pthread_mutex_init(&this->db_read_lock, NULL);

}

bool AccountDataBase::insert_account(int account_id, string password, int initial_amount) {
    Account *temp = new Account(account_id, password, initial_amount);
    if (temp == NULL) {
        return false;
    }
    std::pair<std::map<int, Account *>::iterator, bool> ret;
    ret = this->_Accounts.insert(std::pair<int, Account *>(account_id, temp));
    if (ret.second == false) {
        delete(temp);
        return false;
    }
    return true;
}

void AccountDataBase::readers_lock() {
    pthread_mutex_lock(&this->db_read_lock);
    this->rd_count++;
    if (this->rd_count == 1)
        pthread_mutex_lock(&this->db_write_lock);
    pthread_mutex_unlock(&this->db_read_lock);
}

void AccountDataBase::readers_unlock() {
    pthread_mutex_lock(&this->db_read_lock);
    this->rd_count--;
    if (this->rd_count == 0) {
        pthread_mutex_unlock(&this->db_write_lock);
    }
    pthread_mutex_unlock(&this->db_read_lock);
}


Account *AccountDataBase::search_account(int account_id) {
    map<int, Account *>::iterator it;
    it = this->_Accounts.find((account_id));
    if (it!=_Accounts.end())
        return it->second;
    else
    return NULL;

}

bool AccountDataBase::delete_account(int account_id) {
//todo need to what hapend if the key is not on the map
//    todo also to think how will the dinamics will work for the delete
    Account *temp = this->_Accounts[account_id];
    if (temp != NULL) {
        this->_Accounts.erase(account_id);
        delete (temp);
        return true;
    }
    return false;
}

AccountDataBase::~AccountDataBase() {
    pthread_mutex_destroy(&(this->db_read_lock));
    pthread_mutex_destroy(&(this->db_write_lock));

}

