//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_DATA_BASE_ACCOUNTS_H
#define HW2_DATA_BASE_ACCOUNTS_H

#include "Account.h"
#include "IOThreadSave.h"

#include <pthread.h>
#include <map>


/**
 * This Class is the template for our data base "Account Data Base" or ADB this
 * class is in charge of storing the pointers of all the accounts (we use pointer to be sure that each
 * account is unique and be treated as, it also have some multi-thread features "readers writer lock" (home made
 * not the generic pthread_rwlock_t) and a generic map container STL
 *
 */
class AccountDataBase {

public:


    AccountDataBase();
    virtual ~AccountDataBase();

    /** Insert Account
     * This method will create an account and will try to insert it to the STL map
     * @param account_id
     * @param password
     * @param initial_amount
     * @return true - if the account was succesfully created and add to the map
     *         false - if the account already exist, or we reach an memory allocation problem
     */
    bool insert_account(int account_id, string password, int initial_amount);

    /** Search Account
     * This method will search on the STL map for an espesific account
     * @param account_id
     * @return A pointer - to the account if found
     *          NULL    - if not in the container
     */
    Account * search_account(int account_id);

    /** Delete Account
     * this method will delete the Account from the container and relese the memory
     * @param account_id
     * @return True if the Account was delete
     *          False if the account is not in the STL
     */
    bool delete_account(int account_id);

    /** Bank Print and Charge
     * We declare the next two functions as friend to give then access to the private methods of this class (da :D)
     * @return
     */
    friend void * bank_print(void * arg);
    friend void * bank_charge(void * arg);

    /**Readers lock and unlock
     * This methods are in charge of locking and unlocking the mutex for
     * the readers code (readers writer problem )
     * (we didn't made a writer lock unlock because is a one line function pthread_mutex_lock(&writer_mutex)
     */
    void readers_lock();
    void readers_unlock();

    pthread_mutex_t db_write_lock;
    pthread_mutex_t db_read_lock;
    int rd_count;

private:
    std::map<int,Account*> _Accounts;
    int _balance;
};


#endif //HW2_DATA_BASE_ACCOUNTS_H
