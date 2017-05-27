
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "Atm.h"
#include "Bank.h"

using namespace std;


//TODO: create a destructor for all the class witch will destroy the relevant locks
class Args {
public:
    Args(AccountDataBase *accountDataBase, IOThreadSave *ioThreadSave, char *text, int Atm_number) : accountDataBase(
            accountDataBase),
                                                                                                      ioThreadSave(
                                                                                                              ioThreadSave),
                                                                                                      text(text),
                                                                                                      Atm_number(
                                                                                                              Atm_number) {}

    Args() {}

    int Atm_number;
    AccountDataBase *accountDataBase;
    IOThreadSave *ioThreadSave;
    char *text;

};

void *atm_thread(void *arg) {
    Args *temp = (Args *) arg;
    string path_file = string(temp->text);

    printf((char *) arg);
    //(*temp->Atm_number)++;
    Atm ATM(temp->Atm_number, temp->accountDataBase, temp->ioThreadSave);
    ATM.do_commands(path_file);
    pthread_exit(NULL);
}

void *bank_thread(void *args) {
    Args *temp = (Args *) args;
    Bank bank1(0, "0000", 0, temp->accountDataBase, temp->ioThreadSave);
    bank1.bank_run();
    pthread_exit(NULL);
}

int main(int argc, char **argv) {

    IOThreadSave IOTS("./log.txt");
    AccountDataBase ADB;


    int N = 1; /// supposed to be input arg

    Args bank_arguments(&ADB, &IOTS, "", NULL);
    Args Atm_arguments[10];

    pthread_t threads[N + 1];
    pthread_t bank_thread_hello;
    void *paths[N];
    for (int i = 0; i < N; i++) {
        Atm_arguments[i].Atm_number = i;
        Atm_arguments[i].ioThreadSave = &IOTS;
        Atm_arguments[i].accountDataBase = &ADB;
        Atm_arguments[i].text = argv[i + 1];/// input arg maybe more
    }

    pthread_create(&bank_thread_hello, NULL, bank_thread, (void *) &bank_arguments);
    for (int i = 1; i < N + 1; i++) {
        pthread_create(&threads[i], NULL, atm_thread, (void *) &Atm_arguments);
    }
    for (int i = 1; i < N + 1; i++) {
        pthread_join(threads[i], NULL);
    }
//	exit(NULL);//for bank ,check usage
    return 0;
}