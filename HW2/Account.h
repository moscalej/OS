

#ifndef HW2_ACCOUNT_H
#define HW2_ACCOUNT_H

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <mutex>


using namespace std;

class Account {

public:
    Account(int id, string password, int initial_amount);

    bool check_password( string try_password);
    void deposit(int amount);
    void withdraw( int amount);
    void check_balance();
    void print();
    sem_t lock_write;
    sem_t lock_read;


private:
    string _password;
    int _id;
    int _balance;


};

#endif