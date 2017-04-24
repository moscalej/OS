#ifndef _SIGS_H
#define _SIGS_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include "commands.h"
using namespace std;


class SignalHandler {
public:
	int sendSig(int pID, int sigNum);

	string sigNumToName(int signum);

	void handleSIGTSTP(int status);//CTRL Z

	void handleSIGCHLD(int parameter, siginfo_t *info, void *funtion);// END OF PROCESS

	void handleSIGINT(int status);//ctrl c

	Smash_handler jobs_and_history;
private:

};




#endif

