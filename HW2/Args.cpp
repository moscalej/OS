//
// Created by alejandro on 5/29/2017.
//

#include <unistd.h>
#include "Args.h"
using namespace std;
void * bank_print(void * arg){
    Args * temp = (Args *) arg;
    pthread_mutex_lock(&temp->accountDataBase->db_write_lock);
    std::map<int,Account*>::iterator it;

    for (it = temp->accountDataBase->_Accounts.begin(); it != temp->accountDataBase->_Accounts.end(); ++it) {

        cout<<"Account " <<it->second->_id<< ": Balance -"<<it->second->check_balance() <<
              " $ , Account Password - " << it->second->_password << endl;
    }
    pthread_mutex_unlock(&(temp->accountDataBase->db_write_lock));
    usleep(500000);
}

void * bank_charge(void * arg){
    Args * temp = (Args *) arg;

    pthread_mutex_lock(&temp->accountDataBase->db_read_lock);
    std::map<int,Account*>::iterator it;

    for (it = temp->accountDataBase->_Accounts.begin(); it != temp->accountDataBase->_Accounts.end(); ++it) {
        pthread_mutex_lock(&(it->second->write_lock));

    }

    pthread_mutex_unlock(&(temp->accountDataBase->db_read_lock));

    usleep(500000);
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
