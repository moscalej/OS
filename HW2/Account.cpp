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

    this->_balance = _balance + amount;
    return;

}

bool Account::withdraw(int amount) {

    if (this->_balance < amount)
        return false;
    else {

        this->_balance = _balance - amount;
    }
   return true;
}

int Account::check_balance() {

    return _balance;
}



