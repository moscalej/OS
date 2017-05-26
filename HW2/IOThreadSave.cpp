//
// Created by alejandro on 5/26/2017.
//

#include <cstdio>
#include "IOThreadSave.h"

void IOThreadSave::save_to_log(string to_write_doc) {
    pthread_mutex_lock( &(this->mutex_log));
    FILE * p_file;
    p_file = fopen(this->_path_to_print.c_str(),"a");
    if (p_file!=NULL)
    {
        fputs(to_write_doc.c_str(),p_file);
        fclose (p_file);
    }
    pthread_mutex_unlock(&(this->mutex_log));
}

IOThreadSave::IOThreadSave(string path_to_print) : _path_to_print(path_to_print) {
    mutex_log = PTHREAD_MUTEX_INITIALIZER;
}

IOThreadSave::~IOThreadSave() {
    pthread_mutex_destroy(&(this->mutex_log));
}
