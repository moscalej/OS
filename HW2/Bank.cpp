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

void Bank::print() {
    pthread_mutex_lock(&this->_ADT->db_write_lock);
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
    for (it = _ADT->_Accounts.begin(); it != _ADT->_Accounts.end(); ++it) {

        pthread_mutex_lock(&this->_ADT->db_read_lock);
        this->_ADT->rd_count++;
        if (this->_ADT->rd_count == 1)
            pthread_mutex_lock(&this->_ADT->db_write_lock);
        pthread_mutex_unlock(&this->_ADT->db_read_lock);
        pthread_mutex_lock(&it->second->write_lock);

        int amount;
        amount = int(it->second->_balance * this->_commission_rate);
        if (it->second->withdraw(amount)) {
            this->_balance += amount;/// todo print message
        }
        pthread_mutex_unlock(&it->second->write_lock);

        pthread_mutex_lock(&this->_ADT->db_read_lock);
        this->_ADT->rd_count--;
        if (this->_ADT->rd_count == 0)
            pthread_mutex_unlock(&this->_ADT->db_write_lock);
        pthread_mutex_unlock(&this->_ADT->db_read_lock);
    }
    return;


}

void Bank::bank_run() {

while (true){
//    this->_commission_rate = float(rand() % 100 + 300) / 10000;
//    this->charge_commission();
//    for (int i = 0; i < 6; ++i) {
//        this->print();
//        usleep(1);
//    }
    pthread_rwlock_rdlock(&(this->mutex1));
        if (this->close)break;
    pthread_rwlock_unlock(&(this->mutex1));
}


//    clock_t clock1;
//    int timer=0;
//
//    int timer_print = 0;
//    int timer_change_interest = 0;
//    clock_t zero= clock();
//    while (true) {
//        clock1 = clock() - zero;
//        timer = int(1000* clock1/CLOCKS_PER_SEC);
//
//        if ((timer - timer_change_interest) > 3000) {
//            this->_commission_rate = float(rand() % 100 + 300) / 10000;
//            this->charge_commission();
//            timer_change_interest = timer;
//        }
//        if ((timer - timer_print) > 500) {
//            this->print();
//            timer_print = timer;
//        }
//        pthread_rwlock_rdlock(&(this->mutex1));
//        if (this->close)break;
//        pthread_rwlock_unlock(&(this->mutex1));
//
//    }

}

void Bank::bank_close() {
    pthread_rwlock_wrlock(&(this->mutex1));
    this->close = true;
    pthread_rwlock_unlock(&(this->mutex1));

}

Bank::Bank(int id, string password, int initial_amount, AccountDataBase *ADB, IOThreadSave *IOTS) {
    this->_ADT= ADB;
    this->_IOTS = IOTS;
    this->mutex1 = PTHREAD_RWLOCK_INITIALIZER;
    _balance = initial_amount;
}
