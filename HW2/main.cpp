
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

/*vector<Account> accounts;
void* atm_thread(void* arg) {
    string path_file;
	path_file = *(string*)arg;
	Atm atm(1);
	atm.do_commands(path_file);
	pthread_exit(NULL);
}
void* bank_thread(void * arg) {
    Bank bank(0,"0000",0);
	bank.bank_run();
}
*/

Account acoun1(12,"hola",1000);
Account acoun2(13,"chao",500);

void * funtion1(void *){
	acoun2.check_password("chao");
	acoun2.deposit(125, 0);
}

int main(int argc, char **argv) {

	pthread_t newthtread;

	pthread_create(&newthtread,NULL,funtion1 ,NULL);

	acoun1.deposit(100, 0);
	acoun2.check_password("chao");
	acoun2.deposit(500, 0);


/*
if (argc < 3) {
	fprintf(stderr, "Usage: %s #atm paths", argv[0]);
	exit(1);
}
	int N=(int)argv[1]; /// supposed to be input arg
	pthread_t threads[N + 1];
	string paths[N];
	for (int i=0 i<N; i++)
		 paths[i]=(string)argv[i+2]; /// input arg maybe more
	pthread_create(threads[0], NULL, bank_thread(void *), null);
	for (int i = 1; i < N + 1; i++);
		pthread_create(threads[i], NULL,atm_thread(void *), &path_file);
	for (int i = 1; i < N + 1; i++) {
		pthread_join(threads[i], NULL);
	}
*/
	return 0;
}