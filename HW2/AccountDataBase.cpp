//
// Created by amoscoso on 5/21/2017.
//

#include "AccountDataBase.h"


AccountDataBase::AccountDataBase() {
    rd_count=0;
    _balance=0;
    this->db_write_lock=PTHREAD_MUTEX_INITIALIZER;
    this->db_read_lock=PTHREAD_MUTEX_INITIALIZER;

}

bool AccountDataBase::insert_account(int account_id, string password, int initial_amount) {
     Account * temp = new Account(account_id,password,initial_amount);
    if (temp == NULL){
        return false;
    }
    std::pair<std::map<int,Account *>::iterator,bool> ret;
    ret = this->_Accounts.insert ( std::pair<int,Account*>(account_id,temp) );
    if (!ret.second) {
        return false;
    }
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

AccountDataBase::~AccountDataBase() {
    pthread_mutex_destroy(&(this->db_read_lock));
    pthread_mutex_destroy(&(this->db_write_lock));

}

