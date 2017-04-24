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

	char *sigNumToName(int signum);

	int handleStp(int pID, Process &fg_proc);

	int handleTerm(int pID);

	int handleSleep(int pID);

	Smash_handler jobs_and_history;
private:

};


#endif

