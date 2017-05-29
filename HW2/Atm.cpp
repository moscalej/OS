//
// Created by amoscoso on 5/21/2017.
//

#include <unistd.h>
#include <memory.h>
#include "Atm.h"

#include <cstdlib>


using namespace std;
Atm::Atm(int atm_number, AccountDataBase *ADT, IOThreadSave *IOTS) {
    this-> IOTS = IOTS;
    this->_atm_number=atm_number;
    this->_ADT=ADT; // the idea is that all the atm will have acces to the same ADT

}

void Atm::do_commands(string path) {

    ifstream file(path.c_str());
    if (!file.is_open()) {
        fprintf(stderr, "cannot open trace file\n");
        exit(2);
    }
    string line;

    while (getline(file,line)) {
        if (line  == "\n") {
            file.close();
            break;
        }
        usleep(10000);
        istringstream iss(line);
        string instruction[5];
        int i = 0;
       do{
            iss >> instruction[i] ;
           i++;
        }while (iss);


        if(instruction[0] == "O") {
            this->account(atoi(instruction[1].c_str()), instruction[2], atoi(instruction[3].c_str()));
        }
        if(instruction[0] == "D") {
            this->deposit(atoi(instruction[1].c_str()), instruction[2], atoi(instruction[3].c_str()));
        }
        if(instruction[0] == "W") {
            this->withdraw(atoi(instruction[1].c_str()), instruction[2], atoi(instruction[3].c_str()));
        }
        if(instruction[0] == "B") {
            this->check_balance(atoi(instruction[1].c_str()), instruction[2]);
        }
        if(instruction[0] == "C") {
            this->close_account(atoi(instruction[1].c_str()), instruction[2]);
        }
        if(instruction[0] == "T") {
            this->transfer(atoi(instruction[1].c_str()), instruction[2], atoi(instruction[3].c_str()), atoi(instruction[4].c_str()));
        }

    }


}

void Atm::account(int id, string password, int initial_amount) {
    printMsg msg;

    //newAccount, accountExists, doesntExist, badPassword, success_deposit, insufficient, success_withdraw, balance, success_transfer
    pthread_mutex_lock(&this->_ADT->db_write_lock);

    if (this->_ADT->insert_account(id,password,initial_amount))//todo check if insert to map check duplicity
    {
        msg=newAccount;
    }
    else
        msg=accountExists;

    pthread_mutex_unlock(&this->_ADT->db_write_lock);
    this->IOTS->save_to_log(msg,this->_atm_number,id,password,initial_amount,0,0,0);
    return;
}

void Atm::deposit(int id, string password, int amount) {
    printMsg msg;
    int account_balance=0;
    _ADT->readers_lock();
    Account * temp = this->_ADT->search_account(id);
    if (temp == NULL)
    {

        msg=doesntExist;


    }else {

        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->write_lock);
            sleep(1);
            temp->deposit(amount);
             msg=success_deposit;
            account_balance=temp->check_balance();
            pthread_mutex_unlock(&temp->write_lock);
        } else
             msg=badPassword;
    }
  _ADT->readers_unlock();
    this->IOTS->save_to_log(msg,this->_atm_number,id,password,amount,account_balance,0,0);
    return;


}

void Atm::withdraw(int id, string password, int amount) {
    printMsg msg;
    int account_balance;
    _ADT->readers_lock();
    Account *temp = this->_ADT->search_account(id);

    if (temp == NULL) {
        msg=doesntExist;
    }
    else {
        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->write_lock);
            sleep(1);
            if (temp->withdraw(amount)) {
                msg=success_withdraw;
                account_balance=temp->check_balance();
            }
            else {
                msg=insufficient;
            }
            pthread_mutex_unlock(&temp->write_lock);
        } else {
            msg=badPassword;
        }
    }
    _ADT->readers_lock();
    this->IOTS->save_to_log(msg,this->_atm_number,id,password,amount,account_balance,0,0);
    return;
}

void Atm::check_balance(int id, string password){
    printMsg msg;
    _ADT->readers_lock();
    int account_balance=0;
    Account *temp = this->_ADT->search_account(id);

    if (temp == NULL) {
        msg=doesntExist;

    }
    else {
        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->read_lock);
            sleep(1);
            temp->readers_lock();
            account_balance=temp->check_balance();
            msg=balance;
            temp->readers_unlock();
        } else
            msg=badPassword;
    }
    _ADT->readers_lock();
    this->IOTS->save_to_log(msg,this->_atm_number,id,password,0,account_balance,0,0);
    return;

}

void Atm::close_account(int id, string password){
    printMsg msg;
    pthread_mutex_lock(&this->_ADT->db_write_lock);
    sleep(1);
    Account *temp = this->_ADT->search_account(id);
    if (temp == NULL) {
        msg=doesntExist;

    }
    else {
        if (temp->check_password(password))
        {
            this->_ADT->delete_account(id);
            msg=close;
        }
        else
            msg=badPassword;

    }
    pthread_mutex_unlock(&this->_ADT->db_write_lock);
    this->IOTS->save_to_log(msg,this->_atm_number,id,"",0,0,0,0);
    return;

}

void Atm::transfer(int source_id, string password, int target_id, int amount) {
    printMsg msg;
    bool target_err=false;
    int source_newbalance=0;
    int target_new_balance=0;
    _ADT->readers_lock();
    Account *temp1 = this->_ADT->search_account(source_id);
    Account *temp2 = this->_ADT->search_account(target_id);



    if (temp1 == NULL ) {
         msg=doesntExist;
        target_err=true;


    }
    else
    if (temp2 == NULL ) {
      msg=doesntExist;
    }
    else {
        if (temp1->check_password(password)) {
            if (source_id < target_id) {
                pthread_mutex_lock(&temp1->write_lock);
                pthread_mutex_lock(&temp2->write_lock);
            } else if (source_id==target_id){
                pthread_mutex_lock(&temp1->write_lock);
            }
            else
            {
                pthread_mutex_lock(&temp2->write_lock);
                pthread_mutex_lock(&temp1->write_lock);
            }
            sleep(1);
            if (temp1->withdraw(amount)) {
                temp2->deposit(amount);
                msg=success_transfer;
                source_newbalance=temp1->check_balance();
                target_new_balance=temp2->check_balance();
            } else
                msg=insufficient;
            pthread_mutex_unlock(&temp1->write_lock);
            if (source_id!=target_id)
                pthread_mutex_unlock(&temp2->write_lock);
        } else
            msg=badPassword;
    }
    _ADT->readers_lock();
    if (target_err)
        this->IOTS->save_to_log(msg,this->_atm_number,target_id,password,amount,0,0,0);
    else
        this->IOTS->save_to_log(msg,this->_atm_number,source_id,password,amount,source_newbalance,target_id,target_new_balance);
    return;
}
