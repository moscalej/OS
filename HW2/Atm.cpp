//
// Created by amoscoso on 5/21/2017.
//

#include <unistd.h>
#include "Atm.h"

Atm::Atm(int atm_number, AccountDataBase * ADT) {

    this->_atm_number=atm_number;
    this->_ADT=ADT; // the idea is that all the atm will have acces to the same ADT

}

void Atm::do_commands(string path) {
    string temp[4] ;


}

void Atm::account(int id, string password, int initial_amount) {
    pthread_mutex_lock(&this->_ADT->db_write_lock);
     if (this->_ADT->insert_account(id,password,initial_amount))//todo check if insert to map check duplicity
    {
        cout << _atm_number<<"New account id is "<<id<<"with password "<<password<<" and initial balance "<<initial_amount <<endl;
    }
    else
    cout << "Error " <<this->_atm_number<<" Your transaction failed - account with same id exists" <<endl;
    pthread_mutex_unlock(&this->_ADT->db_write_lock);
    return;
}

void Atm::deposit(int id, string password, int amount) {
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account * temp = this->_ADT->search_account(id);
    if (temp == NULL)
    {
        cout << "Error " <<this->_atm_number<<" Your transaction failed - account "<<id<<" does not exist" <<endl;

    }else {

        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->write_lock);
            sleep(1);
            temp->deposit(amount);
            cout << _atm_number << " account " << id << " new balance is " << temp->check_balance() << " after "
                 << amount << "was deposited" << endl;
            pthread_mutex_unlock(&temp->write_lock);
        } else
            cout << "Error " << this->_atm_number << " Your transaction failed - password for account " << id
                 << " is incorrect" << endl;
    }
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count--;
    if (this->_ADT->rd_count==0)
        pthread_mutex_unlock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);

    return;


}

void Atm::withdraw(int id, string password, int amount) {
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp = this->_ADT->search_account(id);

    if (temp == NULL) {
        cout << "Error " << this->_atm_number << " Your transaction failed - account " << id << " does not exist"
             << endl;
    }
    else {
        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->write_lock);
            sleep(1);
            if (temp->withdraw(amount))
                cout << _atm_number << " account " << id << " new balance is " << temp->check_balance() << " after "
                     << amount << "was withdrew" << endl;
            else
                cout << "Error " << this->_atm_number << " Your transaction failed - account " << id
                     << " balance is lower than " << amount << endl;
            pthread_mutex_unlock(&temp->write_lock);
        } else
            cout << "Error " << this->_atm_number << " Your transaction failed - password for account " << id
                 << " is incorrect" << endl;
    }
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count--;
    if (this->_ADT->rd_count==0)
        pthread_mutex_unlock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    return;
}

void Atm::check_balance(int id, string password){
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp = this->_ADT->search_account(id);

    if (temp == NULL) {
        cout << "Error " << this->_atm_number << " Your transaction failed - account " << id << " does not exist"
             << endl;

    }
    else {
        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->read_lock);
            sleep(1);
            temp->rd_count++;
            if (temp->rd_count == 1)
                pthread_mutex_lock(&temp->write_lock);
            pthread_mutex_unlock(&temp->read_lock);
            cout << _atm_number << " account " << id << " balance is " << temp->check_balance() << endl;
            pthread_mutex_lock(&temp->read_lock);
            temp->rd_count--;
            if (temp->rd_count == 0)
                pthread_mutex_unlock(&temp->write_lock);
            pthread_mutex_unlock(&temp->read_lock);
        } else
            cout << "Error " << this->_atm_number << " Your transaction failed - password for account " << id
                 << " is incorrect" << endl;
    }
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count--;
    if (this->_ADT->rd_count==0)
        pthread_mutex_unlock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    return;

}

void Atm::close_account(int id, string password){
    pthread_mutex_lock(&this->_ADT->db_write_lock);
    sleep(1);
    Account *temp = this->_ADT->search_account(id);
    if (temp == NULL) {
        cout << "Error " << this->_atm_number << " Your transaction failed - account " << id << " does not exist"
             << endl;

    }
    else {
        if (temp->check_password(password))
            this->_ADT->delete_account(id);
        else
            cout << "Error " << this->_atm_number << " Your transaction failed - password for account " << id
                 << " is incorrect" << endl;

    }
    pthread_mutex_unlock(&this->_ADT->db_write_lock);
    return;

}

void Atm::transfer(int source_id, string password, int target_id, int amount) {
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);

    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp1 = this->_ADT->search_account(source_id);
    Account *temp2 = this->_ADT->search_account(target_id);



    if (temp1 == NULL ) {
        cout << "Error " << this->_atm_number << " Your transaction failed - account " << source_id << " does not exist"
             << endl;

    }
    else
    if (temp2 == NULL ) {
        cout << "Error " << this->_atm_number << " Your transaction failed - account " << target_id << " does not exist"
             << endl;
    }
    else {
        if (temp1->check_password(password)) {
            if (source_id < target_id) {
                pthread_mutex_lock(&temp1->write_lock);
                pthread_mutex_lock(&temp2->write_lock);
            } else {
                pthread_mutex_lock(&temp2->write_lock);
                pthread_mutex_lock(&temp1->write_lock);
            }
            sleep(1);
            if (temp1->withdraw(amount)) {
                temp2->deposit(amount);
                cout << _atm_number << "Transfer from account " << source_id << " to account " << target_id
                     << " new account balance is  "
                     << temp1->check_balance() << " new target account balance is " << temp2->check_balance() << endl;
            } else
                cout << "Error " << this->_atm_number << " Your transaction failed - account " << source_id
                     << " balance is lower than " << amount << endl;
            pthread_mutex_unlock(&temp2->write_lock);
            pthread_mutex_unlock(&temp1->write_lock);
        } else
            cout << "Error " << this->_atm_number << " Your transaction failed - password for account " << source_id
                 << " is incorrect" << endl;
    }
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count--;
    if (this->_ADT->rd_count==0)
        pthread_mutex_unlock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    return;
}
