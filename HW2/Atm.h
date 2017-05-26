//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_ATM_H
#define HW2_ATM_H

#include "AccountDataBase.h"




class Atm {
public:

    Atm(int atm_number, AccountDataBase * ADT);

    /**
     * This method will run the Atm:
     * it will open the txt file indicate on the path and run all the commands
     * for the ATM
     * @param path the path to the txt comand file
     */
    void do_commands(string path);

private:
    /**
     * This method will Create an account on the data base
     * it will also print if it it was able to made the account
     * @param id Account id
     * @param password The password corresponding to the id
     * @param initial_amount The accound initial id
     */
    void account(int id,string password, int initial_amount);

    /**
     * This method will make a deposit to the source account
     * it will also print if it it was able to made the deposit
     * and the details
     * @param id : user id
     * @param password  :user password
     * @param amount : amount of the deposit
     */
    void deposit(int id,string password, int amount);

    /**
     * This method will withdraw money from the user account
     * it will also print if it it was able to made the withdraw
     * and the details
     * @param id : user id
     * @param password  :user password
     * @param amount : amount of the deposit
     */
    void withdraw(int id,string password, int amount);

    /**
     * This method will check the balance on the target id
     * it will also print if it it was able to check the balance
     * and the details
     * @param id : user id
     * @param password  :user password
     * @return the balance in the account
     */
    void check_balance(int id, string password);
    void close_account(int id, string password);

    /**
     * This method will made a transaction from user source to user target
     * @param password  :user password
     * @param source_id
     * @param target_id
     * @param amount : amount of the deposit
     * @return if the transaction was made
     */

    void transfer(int source_id, string password, int target_id, int amount);
    int _atm_number;
    AccountDataBase * _ADT;
};








#endif //HW2_ATM_H
