//
// Created by alejandro on 5/23/2017.
//

#include "Account.h"

Account::Account(int id, string password, int initial_amount) {
    this->write_lock = PTHREAD_MUTEX_INITIALIZER;
    this->read_lock = PTHREAD_MUTEX_INITIALIZER;
    this->_id = id;
    this->_password = password;
    this->_balance = initial_amount;
    rd_count=0;
}




bool Account::check_password(string try_password) {
    return this->_password == try_password;
}

void Account::deposit(int amount) {
    pthread_mutex_lock(&write_lock);
    this->_balance = _balance + amount;
    pthread_mutex_unlock(&write_lock);
    return;

}

bool Account::withdraw(int amount) {
    pthread_mutex_lock(&write_lock);
    if (this->_balance < amount)
        return false;
    else {

        this->_balance = _balance - amount;

    }
    pthread_mutex_unlock(&write_lock);
   return true;
}

int Account::check_balance() {
    readers_lock();
    int balance= _balance;
    readers_unlock();
    return balance;
}

Account::~Account() {
    pthread_mutex_destroy(&(this->write_lock));
    pthread_mutex_destroy(&(this->read_lock));
}
void Account::readers_lock() {
    pthread_mutex_lock(&this->write_lock);
    this->rd_count++;
    if (this->rd_count == 1)
        pthread_mutex_lock(&this->write_lock);
    pthread_mutex_unlock(&this->read_lock);
}

void Account::readers_unlock() {
    pthread_mutex_lock(&this->read_lock);
    this->rd_count--;
    if (this->rd_count == 0) {
        pthread_mutex_unlock(&this->write_lock);
    }
    pthread_mutex_unlock(&this->read_lock);
}



