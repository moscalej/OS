//
// Created by alejandro on 5/26/2017.
//

#ifndef HW2_IOTHREADSAVE_H
#define HW2_IOTHREADSAVE_H



#include "AccountDataBase.h"
typedef enum printMsg {newAccount, accountExists, doesntExist, badPassword, success_deposit, insufficient, success_withdraw, balance, success_transfer} printMsg;
class IOThreadSave {
public:

    IOThreadSave(string path_to_print);

    void save_to_log(string type, int atm_num, int id, string password, int amount, int source_balance,
                         int target_balance);

    virtual ~IOThreadSave();



private:

    pthread_mutex_t mutex_log;
    string _path_to_print;
};


#endif //HW2_IOTHREADSAVE_H
