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
#include "commands.h"
#include "signals.h"
#define MAX_LINE_SIZE 80
#define MAXARGS 20

char* L_Fg_Cmd;
void* jobs = NULL; //This represents the list of jobs. Please change to a preferred type (e.g array of char*)
char lineSize[MAX_LINE_SIZE];
SignalHandler Smash01_handler;

void func_handler_TSTP(int parameter){
	Smash01_handler.handleSIGTSTP(parameter);
}
void func_handler_INT(int paramater){
	Smash01_handler.handleSIGINT(paramater);
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

	
	//signal declaretions
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	 /* add your code here */
	
	/************************************/
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	//set your signal handlers here
	/* add your code here */

	struct sigaction TSTP, INT, CHLD;



	//handler for SIGTSTP
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
	// Init globals 


	
	L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
	if (L_Fg_Cmd == NULL) 
			exit (-1); 
	L_Fg_Cmd[0] = '\0';
	
    	while (1)
    	{
	 	printf("smash > ");
		fgets(lineSize, MAX_LINE_SIZE, stdin);
		strcpy(cmdString, lineSize);    	
		cmdString[strlen(lineSize)-1]='\0';
					// perform a complicated Command
		if(!ExeComp(lineSize)) continue; 
					// background command	
	 	//if(!BgCmd(lineSize, jobs)) continue; //todo check if this
					// built in commands
		ExeCmd(jobs, lineSize, cmdString);
		
		/* initialize for next line read*/
		lineSize[0]='\0';
		cmdString[0]='\0';
	}
    return 0;
}

