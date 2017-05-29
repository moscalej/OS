//
// Created by alejandro on 5/29/2017.
//

#include <unistd.h>
#include <cstdlib>
#include "Args.h"
using namespace std;



void * bank_print(void * arg){

    Args * temp = (Args *) arg;
    std::map<int,Account*>::iterator it;
    while (true){
        printf("\033[2J");
        printf("\033[1;1H");
        cout<<"Current Bank status"<<endl;

        pthread_mutex_lock(&temp->accountDataBase->db_write_lock);

        for (it = temp->accountDataBase->_Accounts.begin(); it != temp->accountDataBase->_Accounts.end(); ++it) {

            cout<<"Account " <<it->second->_id<< ": Balance -"<<it->second->_balance <<
                " $ , Account Password - " << it->second->_password << endl;

        }
        cout<<"The Bank has "<<temp->accountDataBase->_balance<<" $"<<endl;
        pthread_mutex_unlock(&(temp->accountDataBase->db_write_lock));

        pthread_rwlock_rdlock(temp->finish_thread);// this check if is time to finish :D
        if(*temp->finish_bool) break;
        pthread_rwlock_unlock(temp->finish_thread);
        usleep(500000);

    }
    pthread_rwlock_unlock(temp->finish_thread);
    pthread_exit(NULL);
}

void * bank_charge(void * arg){

    Args *temp = (Args *) arg;
    std::map<int, Account *>::iterator it;
    while (true) {

        int amount = 0;
        float interest = (rand() % 100 + 300) / 10000;
        for (it = temp->accountDataBase->_Accounts.begin(); it != temp->accountDataBase->_Accounts.end(); ++it) {
            temp->accountDataBase->readers_lock();
            amount = (int) (it->second->_balance * interest);
            it->second->withdraw(amount);
            temp->accountDataBase->_balance += amount;
            temp->accountDataBase->readers_unlock();
            temp->ioThreadSave->Bank_to_Log(interest, amount, it->first);
        }
        pthread_rwlock_rdlock(temp->finish_thread); // this check if is time to finish :D
        if(temp->finish_bool) break;
        pthread_rwlock_unlock(temp->finish_thread);
        sleep(3);
    }
    pthread_rwlock_unlock(temp->finish_thread);
    pthread_exit(NULL);
}



void *atm_thread(void *arg) {
    Args *temp = (Args *) arg;
    string path_file = string(temp->text);

    printf((char *) arg);
    Atm ATM(temp->Atm_number, temp->accountDataBase, temp->ioThreadSave);
    ATM.do_commands(path_file);
    pthread_exit(NULL);
}

Args::Args(AccountDataBase *accountDataBase, IOThreadSave *ioThreadSave, char *text, int Atm_number,
           pthread_rwlock_t * finish_lock, bool *finish_bool) {
    this->finish_bool =finish_bool;
    this->finish_thread =finish_lock;
    this->accountDataBase = accountDataBase;
    this->ioThreadSave = ioThreadSave;
    this->text = text;
    this->Atm_number = Atm_number;

}
