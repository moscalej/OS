//
// Created by alejandro on 5/29/2017.
//

#include <unistd.h>
#include <cstdlib>
#include "Args.h"
using namespace std;
void * bank_print(void * arg){
    
    while (true){

        Args * temp = (Args *) arg;
        std::map<int,Account*>::iterator it;
        pthread_mutex_lock(&temp->accountDataBase->db_write_lock);

        for (it = temp->accountDataBase->_Accounts.begin(); it != temp->accountDataBase->_Accounts.end(); ++it) {
            it->second->readers_lock();
            cout<<"Account " <<it->second->_id<< ": Balance -"<<it->second->_balance <<
                " $ , Account Password - " << it->second->_password << endl;
            it->second->readers_unlock();
        }
        pthread_mutex_unlock(&(temp->accountDataBase->db_write_lock));
        usleep(500000);
    }
}

void * bank_charge(void * arg){

    while (true) {
        
        Args *temp = (Args *) arg;
        std::map<int, Account *>::iterator it;
        int amount = 0;
        float interest = (rand() % 100 + 300) / 10000;
        for (it = temp->accountDataBase->_Accounts.begin(); it != temp->accountDataBase->_Accounts.end(); ++it) {
            temp->accountDataBase->readers_lock();
            pthread_mutex_lock(&(it->second->write_lock));
            amount = (int) (it->second->_balance * interest);
            it->second->_balance -= amount;
            pthread_mutex_unlock(&(it->second->write_lock));
            temp->accountDataBase->readers_unlock();
            temp->ioThreadSave->Bank_to_Log(interest, amount, it->first);
        }

        sleep(3);
    }
}



void *atm_thread(void *arg) {
    Args *temp = (Args *) arg;
    string path_file = string(temp->text);

    printf((char *) arg);
    Atm ATM(temp->Atm_number, temp->accountDataBase, temp->ioThreadSave);
    ATM.do_commands(path_file);
    pthread_exit(NULL);
}

Args::Args(AccountDataBase *accountDataBase, IOThreadSave *ioThreadSave, char *text, int Atm_number) {
    this->accountDataBase = accountDataBase;
    this->ioThreadSave = ioThreadSave;
    this->text = text;
    this->Atm_number = Atm_number;

}
