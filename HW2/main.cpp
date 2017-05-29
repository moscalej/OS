
#include <stdio.h>
#include <iostream>
#include "Args.h"

using namespace std;


//TODO: create a destructor for all the class witch will destroy the relevant locks

int main(int argc, char **argv) {

    IOThreadSave IOTS("./log.txt");
    AccountDataBase ADB;
    pthread_rwlock_t thread_finish;
    bool finish=false;
    thread_finish =PTHREAD_RWLOCK_INITIALIZER;

    int N = 1; /// supposed to be input arg

    Args bank_arguments(&ADB, &IOTS, NULL, 0, &thread_finish, NULL);
    Args Atm_arguments[N];

    pthread_t threads[N];
    pthread_t bank_print_thread;
    pthread_t bank_charge_thread;

    for (int i = 0; i < N; i++) {
        Atm_arguments[i].Atm_number = i;
        Atm_arguments[i].ioThreadSave = &IOTS;
        Atm_arguments[i].accountDataBase = &ADB;
        Atm_arguments[i].text = argv[i + 1];/// input arg maybe more
    }

    pthread_create(&bank_print_thread, NULL, &bank_print, (void *) &bank_arguments);
    for (int i = 0; i < N ; i++) {
        pthread_create(&threads[i], NULL, atm_thread, (void *) &Atm_arguments);
    }
    pthread_create(&bank_charge_thread, NULL, &bank_charge, (void *) &bank_arguments);
    for (int i = 0; i < N ; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_rwlock_wrlock(&thread_finish);
    finish=true;
    pthread_rwlock_unlock(&thread_finish);

    pthread_join(bank_print_thread,NULL);

//	exit(NULL);//for bank ,check usage
    return 0;
}