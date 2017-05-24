//
// Created by alejandro on 5/23/2017.
//

#include "Account.h"

Account::Account(int id, string password, int initial_amount) {
    this->_id=id;
    this->_password = password;
    this->_balance=initial_amount;
    this->mutex1 = PTHREAD_MUTEX_INITIALIZER;


}

bool Account::deposit(int amount) {
    if(!log_on ) return false;
    this->_balance =_balance+amount;
    this->log_on=false;
    this->log_off();
    return true;

}

void Account::log_off() {
    this->log_on = false;
    pthread_mutex_unlock(&(this->mutex1));
}

bool Account::check_password(string try_password) {
    int i;
    pthread_mutex_lock(&(this->mutex1));
    if(this->_password == try_password){
        this->log_on= true;
    }
    return false;
}
