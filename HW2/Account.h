

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
    void deposit(int amount);

    /**
     * This method will withdraw money from the user account

     * @param amount : amount of the deposit
     * @return true - if the windraw was made
     *          false- if there is not enough money to take
     */
    bool withdraw(int amount);

    /**
     * This method will check the balance on the target id
     * @return the balance in the account
     */
    int check_balance();
    friend void * bank_print(void * arg);

    friend void * bank_charge(void * arg);
    void readers_lock();
    void readers_unlock();
    int _id;
    pthread_mutex_t write_lock;
    pthread_mutex_t read_lock;
    int rd_count;
private:

    string _password;
    int _balance;
};



#endif