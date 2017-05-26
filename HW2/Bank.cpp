//
// Created by amoscoso on 5/21/2017.
//

#include "Bank.h"
#include <time.h>

vector<Account *> Bank::get_acounts() {
    vector<Account *> temp = this->_ADT->get_accounts();
    return temp;
}
//Todo: change the balance of the accounts we need a better way to take money an read the balance

void Bank::print() {
    vector<Account *> temp = this->_ADT->get_accounts();

    string pre_print = "";
    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i] == NULL) continue;
        pre_print.append("Account " + to_string(temp[i]->_id) + ": Balance -" + to_string(temp[i]->_balance)
                         + " $ , Account Password - " + temp[i]->_password + "\n");
    }
    cout << "Current Bank Status" << endl;
    cout << pre_print << end;
    cout << "The Bank has " << this->_balance << " $" << endl;
}

void Bank::charge_comission() {
    vector<Account *> temp = this->_ADT->get_accounts();
    float amount;
    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i] == NULL) continue;
        amount = (temp[i]->_balance * this->_tax_revenew);
        temp[i]->_balance = int(temp[i]->_balance - amount);
        this->_balance += int(amount);
    }
}

void Bank::bank_run() {
    int timer_print=0;
    int timer_charge=0;
    int timer_change_interest=0;

    if (timer_change_interest> 100){
        this->_tax_revenew = float(rand() % 100 + 300)/100;
    }
    if(timer_print>500) this->print();
    if (timer_charge>1000) this->charge_comission();

    time()


}
