/*	smash.c
main file. This file contains the main function of smash
*******************************************************************/

/**
 * this is the homework wet 1 for Operating systems
 * this file was made by:
 * Alejandro Moscoso and Yonathan (dificult last name)
 *
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "signals.h"

#define MAX_LINE_SIZE 80
#define MAXARGS 20


char lineSize[MAX_LINE_SIZE];
SignalHandler Smash01_handler;

void func_handler_TSTP(int parameter){
	Smash01_handler.handleSIGTSTP(parameter);
}
void func_handler_INT(int parameter){
	Smash01_handler.handleSIGINT(parameter);
}
void func_handler_CHILD(int parameter, siginfo_t *info, void *funtion){
	Smash01_handler.handleSIGCHLD(parameter,info,funtion);
}

//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    char cmdString[MAX_LINE_SIZE]; 	   

	

	/**
	//NOTE: the signal handlers and the function/s that sets the handler should be found in signals.c
	//set your signal handlers here
	 */

	struct sigaction TSTP, INT, CHLD;



	//handler for SIGTSTP this is the handler for the Control Z
    sigemptyset(&TSTP.sa_mask);
	TSTP.sa_handler = &func_handler_TSTP ;
    TSTP.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &TSTP, NULL);

	//handler for SIGINT
	sigemptyset(&INT.sa_mask);
	INT.sa_handler = &func_handler_INT;
	INT.sa_flags = SA_RESTART;
	sigaction(SIGINT, &INT, NULL);

	//handler for SIGCHLD
	sigemptyset(&CHLD.sa_mask);
	CHLD.sa_sigaction = &func_handler_CHILD;
	CHLD.sa_flags = SA_SIGINFO;
	sigaction(SIGCHLD, &CHLD, NULL);

    while (1)
    	{
	 	printf("smash > ");
		fgets(lineSize, MAX_LINE_SIZE, stdin);
		strcpy(cmdString, lineSize);    	
		cmdString[strlen(lineSize)-1]='\0';

            ExeCmd(lineSize, cmdString, Smash01_handler);
		

		lineSize[0]='\0';
		cmdString[0]='\0';
	}

}

