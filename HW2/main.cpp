
#include <stdio.h>


#include <iostream>
#include "Args.h"

using namespace std;


//TODO: create a destructor for all the class witch will destroy the relevant locks

int main(int argc, char **argv) {

    IOThreadSave IOTS("./log.txt");
    AccountDataBase ADB;


    int N = 1; /// supposed to be input arg

    Args bank_arguments(&ADB, &IOTS, NULL, 0);
    Args Atm_arguments[N];

    pthread_t threads[N];
    pthread_t bank_thread_hello;

    for (int i = 0; i < N; i++) {
        Atm_arguments[i].Atm_number = i;
        Atm_arguments[i].ioThreadSave = &IOTS;
        Atm_arguments[i].accountDataBase = &ADB;
        Atm_arguments[i].text = argv[i + 1];/// input arg maybe more
    }

    pthread_create(&bank_thread_hello, NULL, bank_thread, (void *) &bank_arguments);
    for (int i = 0; i < N ; i++) {
        pthread_create(&threads[i], NULL, atm_thread, (void *) &Atm_arguments);
    }
    for (int i = 0; i < N ; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_exit(bank_thread_hello);

//	exit(NULL);//for bank ,check usage
    return 0;
}