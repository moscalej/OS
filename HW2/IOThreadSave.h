//
// Created by alejandro on 5/26/2017.
//

#ifndef HW2_IOTHREADSAVE_H
#define HW2_IOTHREADSAVE_H



#include "AccountDataBase.h"
class IOThreadSave {
public:

    IOThreadSave(string path_to_print);

    void save_to_log(string to_write_doc);

    virtual ~IOThreadSave();



private:

    pthread_mutex_t mutex_log;
    string _path_to_print;
};


#endif //HW2_IOTHREADSAVE_H
