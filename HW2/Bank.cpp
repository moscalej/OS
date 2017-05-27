//
// Created by amoscoso on 5/21/2017.
//

#include <unistd.h>
#include "Bank.h"


vector<Account *> Bank::get_accounts() {
    vector<Account *> temp = this->_ADT->get_accounts();
    return temp;
}
//Todo: change the balance of the accounts we need a better way to take money an read the balance
//Todo: finish the print, check for destruck mutex on destructor, change the bank run to work with number of cycles;
//Todo: print on charge conditions on the HW format

void Bank::print() {
    pthread_mutex_lock(&this->_ADT->db_write_lock);
    //Todo remove the vector work, direct from the data base
    vector<Account *> temp = this->_ADT->get_accounts();

    string pre_print = "";
    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i] == NULL) continue;
        pre_print.append("Account " + to_string(temp[i]->_id) + ": Balance -" + to_string(temp[i]->_balance)
                         + " $ , Account Password - " + temp[i]->_password + "\n");
    }
    pthread_mutex_unlock(&this->_ADT->db_write_lock);
    printf("\033[2j");
    printf("\033[1:1h");
    cout << "Current Bank Status" << endl;
//    cout << pre_print << end;
//    cout << "The Bank has " << this->_balance << " $" << endl;
}

void Bank::charge_commission() {
    string to_print;
    for (it = _ADT->_Accounts.begin(); it != _ADT->_Accounts.end(); ++it) {
        pthread_mutex_lock(&this->_ADT->db_read_lock);
        this->_ADT->rd_count++;
        if (this->_ADT->rd_count == 1)
            pthread_mutex_lock(&this->_ADT->db_write_lock);
        pthread_mutex_unlock(&this->_ADT->db_read_lock);
        pthread_mutex_lock(&it->second->write_lock);

        int amount;
        amount = int(it->second->_balance * this->_commission_rate);
        float de_comi=this->_commission_rate;
        if (it->second->withdraw(amount)) {
            this->_balance += amount;// todo print message
             to_print =to_string(de_comi)+"  ";
        }





        pthread_mutex_unlock(&it->second->write_lock);

        pthread_mutex_lock(&this->_ADT->db_read_lock);
        this->_ADT->rd_count--;
        if (this->_ADT->rd_count == 0) {
            pthread_mutex_unlock(&this->_ADT->db_write_lock);
        }
        pthread_mutex_unlock(&this->_ADT->db_read_lock);
        this->_IOTS->save_to_log(to_print);
    }
    return;


}

void Bank::bank_run() {

while (true){
    for (int i = 0; i < 6; ++i) {
        this->print();
        usleep(500000);
        printf("printed%d \n",i);
    }
    this->_commission_rate = float(rand() % 100 + 300) / 10000;
    this->charge_commission();
    pthread_rwlock_rdlock(&(this->mutex1));
        if (this->close)break;
    pthread_rwlock_unlock(&(this->mutex1));
}



}

void Bank::bank_close() {
    pthread_rwlock_wrlock(&(this->mutex1));
    this->close = true;
    pthread_rwlock_unlock(&(this->mutex1));

}


void Bank::set(int initial_amount, AccountDataBase *ADB, IOThreadSave *IOTS) {
    this->_ADT= ADB;
    this->_IOTS = IOTS;
    this->close= false;
    this->mutex1 = PTHREAD_RWLOCK_INITIALIZER;
    _balance = initial_amount;

}
