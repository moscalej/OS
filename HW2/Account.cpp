//
// This document was create it by
//  Alejandro Moscoso and Yonathan Haimovich
//  for the Hw 2 of Operating systems 2017 spring
//

#include <unistd.h>
#include "Account.h"

Account::Account(int id, string password, int initial_amount) {

    pthread_mutex_init(&this->write_lock, NULL);
    pthread_mutex_init(&this->read_lock, NULL);
    this->_id = id;
    this->_password = password;
    this->_balance = initial_amount;
    rd_count = 0;
}

bool Account::check_password(string try_password) {
    return this->_password == try_password;
}

int Account::deposit(int amount) {
    pthread_mutex_lock(&write_lock);
    sleep(1);
    this->_balance = _balance + amount;
    pthread_mutex_unlock(&write_lock);
    return _balance;

}

int Account::withdraw(int amount) {
    pthread_mutex_lock(&write_lock);
    sleep(1);
    if (this->_balance < amount)
        return -1;
    else {

        this->_balance = _balance - amount;
    }
    pthread_mutex_unlock(&write_lock);
    return _balance;
}

int Account::charge_commission(double rate) {
    pthread_mutex_lock(&write_lock);
    int amount = (int) (_balance * rate);
    this->_balance = _balance - amount;
    pthread_mutex_unlock(&write_lock);
    return amount;
}

int Account::check_balance() {
    readers_lock();
    sleep(1);
    int balance = _balance;
    readers_unlock();
    return balance;
}

Account::~Account() {
    pthread_mutex_destroy(&(this->write_lock));
    pthread_mutex_destroy(&(this->read_lock));
}

void Account::readers_lock() {
    pthread_mutex_lock(&this->read_lock);
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

bool Account::transfer(int amount, Account *target_account) {
    bool success;
    if (_id<target_account->_id)
    {
        pthread_mutex_lock(&this->write_lock);
        pthread_mutex_lock(&target_account->write_lock);
        sleep(1);
        if (this->_balance>=amount)
        {
            this->_balance-=amount;
            target_account->_balance+=amount;
            success= true;
        } else {

            success= false;
        }
        pthread_mutex_unlock(&this->write_lock);
        pthread_mutex_lock(&target_account->write_lock);
        return success;
    }
    else if ((_id==target_account->_id))
    {
        return true;
    } else
    {
        pthread_mutex_lock(&target_account->write_lock);
        pthread_mutex_lock(&this->write_lock);
        sleep(1);
        if (this->_balance>=amount)
        {
            this->_balance-=amount;
            target_account->_balance+=amount;

            success= true;
        } else {
            success= false;
        }
        pthread_mutex_unlock(&target_account->write_lock);
        pthread_mutex_unlock(&this->write_lock);
        return success;
    }

}

int Account::get_balance() {
    readers_lock();
    int balance=_balance;
    readers_unlock();
    return balance;
}



