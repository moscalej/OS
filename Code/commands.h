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

class Process{
public:
    Process(string process_name,int proccess_id,int time){
        _process_name = process_name;
        _process_id = proccess_id;
        _time = time;
    }
private:
    string _process_name;
    int _process_id;
    int _time;
};


class History{

public:
    int add_proccess(string process_name);
    int jobs();
    int fore_grond();
    void add_commands(string command);
    int add_proccess(char *process_name, char **args);

private:
   // Process process_backgrond[100];
    string  _commands[50];
    int _number_of_comands=0;
    int _iterator=0;


};




#endif

