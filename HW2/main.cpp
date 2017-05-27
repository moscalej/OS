
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "Atm.h"
#include "Bank.h"

//TODO: create a destructor for all the class witch will destroy the relevant locks
using namespace std;

AccountDataBase ADB;
IOThreadSave IOTS("./log.txt");
int atm_num=0;
void* atm_thread(void* arg) {
    string path_file;
	path_file = string( (char*) arg);
	printf((char *) arg);
	atm_num++;
	Atm ATM(atm_num, &ADB, &IOTS);
	ATM.do_commands(path_file);
	pthread_exit(NULL);
}
void* bank_thread(void * ) {
    Bank bank(0,"0000",0);
	bank.bank_run();
	pthread_exit(NULL);
}

int main(int argc, char **argv) {


//if (argc < 3) {
//	fprintf(stderr, "Usage: %s #atm paths", argv[0]);
//	exit(1);
//}
	int N = 1; /// supposed to be input arg
	pthread_t threads[N + 1];
	void * paths[N];
	for (int i=0; i<N; i++) {
		paths[i] = argv[i + 1];/// input arg maybe more
	}
	pthread_create(&threads[0], NULL, bank_thread, NULL);

	for (int i = 1; i < N + 1; i++) {
		pthread_create(&threads[i], NULL, atm_thread, paths[i - 1]);
	}
	for (int i = 1; i < N + 1; i++) {
		pthread_join(threads[i], NULL);
	}
//	exit(NULL);//for bank ,check usage
	return 0;
}