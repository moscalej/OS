//
// Created by alejandro on 5/26/2017.
//

#ifndef HW2_IOTHREADSAVE_H
#define HW2_IOTHREADSAVE_H
#include <fstream>
#include <sstream>
#include "AccountDataBase.h"

/**
 * Messages code that our Input Output Thread Save (IOTS) understand
 */
typedef enum printMsg {newAccount, accountExists, doesntExist, badPassword, success_deposit, insufficient,
                        success_withdraw, success_balance,success_close, success_transfer} printMsg;

/** Input Output Thread Save (IOTS)
 * This class is in charge of writing all the different logs messages from all the Atm and also from the bank
 * function, we made a class to handle this so we can be sure that it will be multi-thread save, it also
 * give us the option of building templates for all the different messages (this give all the other objects
 * less responsabilities) also this Class is independen(meaning no other class needs to lock the mux, the class
 * does it built-in and unlock it after the Method are finish
 *
 */
class IOThreadSave {
public:

    IOThreadSave();

    virtual ~IOThreadSave();

    /** Atm to Log
     * This method is in charge of creating a message (from one of the templates) and then
     * write it to the log file ensuring multi-threading safety.
     *
     * @param msg - Code for the Template to use
     * @param atm_num
     * @param id
     * @param password
     * @param amount
     * @param source_balance
     * @param target_id
     * @param target_balance
     */
    void save_to_log(printMsg msg, int atm_num, int id, string password, int amount, int source_balance,
                     int target_id, int target_balance);
    /** Bank to Log
     * This method is in charge of creating a message for the bank and then
     * write it to the log file ensuring multi-threading safety.
     * @param interest_rate
     * @param amount_to_charge
     * @param account_id
     */
    void Bank_to_Log(float interest_rate, int amount_to_charge, int account_id);



private:
    ofstream logFile;
    pthread_mutex_t mutex_log;
};


#endif //HW2_IOTHREADSAVE_H
