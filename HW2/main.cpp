//
// This document was create it by
//  Alejandro Moscoso and Yonathan Haimovich
//  for the Hw 2 of Operating systems 2017 spring
//

#include <stdio.h>
#include <iostream>
#include "ThreadFunc.h"

using namespace std;


//TODO: create a destructor for all the class witch will destroy the relevant locks
//TODO: check the paths to the #logs# and to the read folder

int main(int argc, char **argv) {
    if (argc < 3) {
        cout<< "illegal arguments"<<endl;
        exit(1);
    }

    IOThreadSave IOTS;
    AccountDataBase ADB;
    pthread_rwlock_t thread_finish; //for closing threads (bank_charge and print)
    pthread_rwlock_init(& thread_finish,NULL);
    int finish=3;

    int N = argv[1];

    Args bank_arguments(&ADB, &IOTS, NULL, 0, &thread_finish, &finish);
    Args Atm_arguments[N];

    pthread_t threads[N];
    pthread_t bank_print_thread;
    pthread_t bank_charge_thread;

    for (int i = 0; i < N; i++) {
        Atm_arguments[i].Atm_number = i+1;
        Atm_arguments[i].ioThreadSave = &IOTS;
        Atm_arguments[i].accountDataBase = &ADB;
        Atm_arguments[i].text = argv[i + 2];

    }

    pthread_create(&bank_print_thread, NULL, &bank_print, (void *) &bank_arguments);
    for (int i = 0; i < N ; i++) {
        pthread_create(&threads[i], NULL, atm_thread, (void *) &Atm_arguments);
    }
    pthread_create(&bank_charge_thread, NULL, &bank_charge, (void *) &bank_arguments);
    for (int i = 0; i < N ; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_rwlock_wrlock(&thread_finish); //Tells the Bank thread to close
    finish=2;
    pthread_rwlock_unlock(&thread_finish);

    pthread_join(bank_charge_thread,NULL);
    finish=1;                               //Tells the Bank Print to close
    pthread_join(bank_print_thread,NULL);

    //Todo we need to relese all the alocate memery

    return 0;
}