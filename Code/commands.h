/**
 * this is the homework wet 1 for Operating systems
 * this file was made by:
 * Alejandro Moscoso and Yonathan (dificult last name)
 *
 */


#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;


#define MAX_LINE_SIZE 80
#define MAX_ARG 20

//typedef enum { FALSE , TRUE } bool;
int ExeComp(char* lineSize);
int BgCmd(char* lineSize, void* jobs);
int ExeCmd(void* jobs, char* lineSize, char* cmdString);
void ExeExternal(char *args[MAX_ARG], char* cmdString);


/**
 * This class will store the process data need it
 */
class Process{
public:
    Process ();
    Process(string process_name,int proccess_id,int time){
        _process_name = process_name;
        _process_id = proccess_id;
        _time = time;
    }

    string _process_name;
    int _process_id;
    int _time;
};


/**
 * Class History: this class will be in charge of handling the system call
 *      and also the history of the commands and the process run by the user
 *
 */
class History{

public:

    /**
     * Adds a procces to the background afterwards
     * @param process_name - Name of the process to run
     * @param args - a vector of arguments to pass to the program
     * @return  0 -if the process was successfully set
     *         1 - otherwise
     */
    int add_proccess(char *process_name, char **args);

    /**
     * This method will print all the jobs running on the
     * background
     * @return 0 -if the process was successfully set
     *         1 - otherwise
     */
    int jobs();

    /**
     * This method will set a process to the foreground
     *
     * work with the information provide by the jobs
     * method
     * @param place - is the place on the jobs history
     * @return 0 -if the process was successfully set
     *         1 - otherwise
     */
    int foreground(int place);

    /**
     * This method will add the process name to the list of process
     * it can only hold the last 50 entrys
     * @param command - name of the process
     */
    void add_commands(string command);

    /**
     * this method will print the history of the commands
     */
    void print_history();

    /**
     * This method will set a process to the foreground
     *
     * work with the information provide by the jobs
     * method
     * @param place - is the place on the jobs history
     * @return 0 -if the process was successfully set
     *         1 - otherwise
     */
    void background(int place);

private:
    Process _process_running[100];
    string  _commands[50];
    int _number_of_comands=0;
    int _iterator=0;
    int _number_of_process;


};




#endif

