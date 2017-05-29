//
// Created by alejandro on 5/26/2017.
//

#ifndef HW2_IOTHREADSAVE_H
#define HW2_IOTHREADSAVE_H
#include <fstream>
#include <sstream>
#include "AccountDataBase.h"
typedef enum printMsg {newAccount, accountExists, doesntExist, badPassword, success_deposit, insufficient, success_withdraw, balance, success_transfer} printMsg;
class IOThreadSave {
public:

    IOThreadSave();
    void save_to_log(printMsg msg, int atm_num, int id, string password, int amount, int source_balance,
                     int target_id, int target_balance);
    void Bank_to_Log(int rate, int amount, int id);
    virtual ~IOThreadSave();



private:
    ofstream logFile;
    pthread_mutex_t mutex_log;
    string _path_to_print;
};


#endif //HW2_IOTHREADSAVE_H
