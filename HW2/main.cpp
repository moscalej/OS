
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include "Account.h"
//#include "Atm.h"
//#include "Bank.h"
//#include <vector>

using namespace std;

AccountDataBase ADB;
int atm_num=0;
void* atm_thread(void* arg) {
    string path_file;
	path_file = (string)*arg;
	atm_num++;
	Atm ATM(atm_num,&ADB);
	ATM.do_commands(path_file);
	pthread_exit(NULL);
}
void* bank_thread(void * arg) {
    Bank bank(0,"0000",0);
	bank.bank_run();
}

int main(int argc, char **argv) {


if (argc < 3) {
	fprintf(stderr, "Usage: %s #atm paths", argv[0]);
	exit(1);
}
	int N=(int)argv[1]; /// supposed to be input arg
	pthread_t threads[N + 1];
	string paths[N];
	for (int i=0; i<N; i++) {
		paths[i] = (string) argv[i + 2];/// input arg maybe more
	}
	pthread_create(threads[0], NULL, bank_thread, NULL);
	for (int i = 1; i <= N + 1; i++);
		pthread_create(threads[i], NULL,atm_thread, &path[i-1]);
	for (int i = 1; i < N + 1; i++) {
		pthread_join(threads[i], NULL);
	}
	exit(NULL);//for bank ,check usage
	return 0;
}