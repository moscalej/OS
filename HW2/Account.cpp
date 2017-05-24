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

bool Account::deposit(int amount, int service_number) {
    if(!log_on || (this->_service_number != service_number)) return false;
    this->_balance =_balance+amount;
    this->log_on=false;
    this->log_off();
    return true;

}

void Account::log_off() {
    this->log_on = false;
    pthread_mutex_unlock(&(this->mutex1));
}

int Account::check_password(string try_password) {
    int service_number;
    pthread_mutex_lock(&(this->mutex1));
    if(this->_password == try_password){
        this->log_on= true;
        service_number=rand();
        this->_service_number = service_number;
        return  service_number;
    }
    return -1;
}
