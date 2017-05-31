//
// This document was create it by
//  Alejandro Moscoso and Yonathan Haimovich
//  for the Hw 2 of Operating systems 2017 spring
//

#ifndef HW2_ACCOUNT_H
#define HW2_ACCOUNT_H

#include <iostream>
#include <pthread.h>


using namespace std;

class Account {

public:
    virtual ~Account();
    Account(int id, string password, int initial_amount);

    /**
     * This method will check if the password is corret
     * @param try_password : password to compare
     * @return true if the passwords match false if not
     */
    bool check_password(string try_password);

    /**
    * This method will make a deposit to the source account
    *
    * @param amount : amount of the deposit
    */
    int deposit(int amount);

    /**
     * This method will withdraw money from the user account

     * @param amount : amount of the deposit
     * @return true - if the windraw was made
     *          false- if there is not enough money to take
     */
    int withdraw(int amount);
    int charge_commission(double rate);
    /**
     * This method will check the balance on the target id
     * @return the balance in the account
     */
    int check_balance();
    bool transfer(int amount,Account *target_account);
    int get_balance();
    /**
     * The next to methods are the ones use by the bank threads
     * we made then friend so the bank can access the private arguments
     * of the Accounts
     * @param arg
     * @return
     */
    friend void * bank_print(void * arg);
    friend void * bank_charge(void * arg);

    /**
     *These methods and rd_count are the readers code for the ReadWrithe problem
     * we also use pthread_rwlock_t on parts of our code to keep the things simple
     * but in these case we made it by hand :D
     */
    void readers_lock();
    void readers_unlock();
    pthread_mutex_t write_lock;
    pthread_mutex_t read_lock;
    int rd_count;


    int _id;
private:

    string _password;
    int _balance;
};



#endif