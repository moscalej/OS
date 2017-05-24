

#ifndef HW2_ACCOUNT_H
#define HW2_ACCOUNT_H

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <mutex>
#include <random>


using namespace std;

class Account {

public:
    Account(int id, string password, int initial_amount);
    Account( const Account&);

    /**
     * This method will check if the password is corret
     * @param try_password : password to compare
     * @return true if the passwords match false if not
     */
    int check_password(string try_password);

    /**
    * This method will make a deposit to the source account
    *
    * @param amount : amount of the deposit
    */
    bool deposit(int amount, int service_number);

    /**
     * This method will withdraw money from the user account

     * @param amount : amount of the deposit
     * @return true - if the windraw was made
     *          false- if there is not enough money to take
     */
    bool withdraw(int amount, int service_number);

    /**
     * This method will check the balance on the target id
     * @return the balance in the account
     */
    int check_balance(int service_number);

    int _id;

private:
    void log_off();
    pthread_mutex_t mutex1;
    bool log_on;
    string _password;
    int _balance;
    int _service_number;
};



#endif