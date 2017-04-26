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

    /*todo i think this handler is call every time a child process change his state, if so this could be the bug
    becouse every time the process change from running to stoped will send a signal to the parent*/

	void handleSIGCHLD(int parammeter, siginfo_t *info, void *function);// END OF PROCESS or change

	void handleSIGINT(int status);//ctrl c

	Smash_handler jobs_and_history;
private:

};


//typedef enum { FALSE , TRUE } bool;
int ExeComp(char* lineSize);
int BgCmd(char* lineSize, void* jobs);
int ExeCmd(void *jobs, char *lineSize, char *cmdString, SignalHandler &Handler);
void ExeExternal(char *cmdString, char *args[20], SignalHandler &Handler);




#endif

