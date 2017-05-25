//
// Created by amoscoso on 5/21/2017.
//

#include "Atm.h"

Atm::Atm(int atm_number, AccountDataBase * ADT) {
    this->_atm_number=atm_number;
    this->_ADT=ADT; // the idea is that all the atm will have acces to the same ADT

}

void Atm::do_commands(string path) {
    string temp[4] ;


}

bool Atm::account(int id, string password, int initial_amount) {
    return this->_ADT->insert_account(id,password,initial_amount);

}

bool Atm::deposit(int id, string password, int amount) {

    Account * temp = this->_ADT->search_account(id);
    if (temp == NULL) return false;
    int service_number = temp->check_password(password);

    return temp->deposit(amount,service_number);
}

bool Atm::withdraw(int id, string password, int amount) {
    Account * temp = this->_ADT->search_account(id);
    if (temp == NULL) return false;
    int service_number = temp->check_password(password);
    return temp->withdraw(amount,service_number);
}
