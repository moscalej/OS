//
// Created by amoscoso on 5/21/2017.
//
#include "AccountDataBase.h"

AccountDataBase::AccountDataBase() {

    this->rwlock=PTHREAD_RWLOCK_INITIALIZER;

}
