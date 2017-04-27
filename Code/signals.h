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

/**
 * This class is in charge of the signal handling and with the help
 * of the Command Handler it can manage all the external/complicate
 * commands
 */
class SignalHandler {
public:

    /**
     * This method will send a signal
     * @param pID - address of the process
     * @param sigNum - Number of the signal
     * @return
     */
	int sendSig(int pID, int sigNum);

    /**
     * This method will translate the signal
     * number to the Name
     * @param signum - signal number
     * @return name of the signal
     */
	string sigNumToName(int signum);

	/**
	 * This is the method in charge of handling
	 * the stop signals coming from Control-Z
	 * @param status - this parameter is not use;
	 */
	void handleSIGTSTP(int status);//CTRL Z

	/**
	 * This method will handle the Child signals
	 * check their status and their place on the jobs list
	 */
	void handleSIGCHLD(int parammeter, siginfo_t *info, void *function);// END OF PROCESS or change


	/**
	 * This method will handle the Finish signals Control + c
	 */
	void handleSIGINT(int status);//ctrl c

	/**
	 * this will handle the rest of the commands a full
	 * description is provide on the interface of this
	 * module
	 */
	Smash_handler jobs_and_history;
private:

};



int ExeComp(char* lineSize);
int BgCmd(char* lineSize, void* jobs);
int ExeCmd(char *lineSize, char *cmdString, SignalHandler &Handler);
void ExeExternal(char *cmdString, char *args[20], SignalHandler &Handler);




#endif

