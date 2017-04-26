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

/**
 * This class will store the process data need it
 */
class Process{
public:

    string _process_name;
    int _process_id;
    int _time;
    bool is_stop;

};


/**
 * Class History: this class will be in charge of handling the system call
 *      and also the history of the commands and the process run by the user
 *
 */
class Smash_handler{

public:

    Smash_handler();
    /**
     * Adds a procces to the background afterwards
     * @param process_name - Name of the process to run
     * @param args - a vector of arguments to pass to the program
     * @return  0 -if the process was successfully set
     *         1 - otherwise
     */
    int Start_process(char *process_name, char **args);

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
     *         (-1) - otherwise
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

    /**
     * This method will add a Process to the background  process list
     * @param Process_name - The name given in the command line
     * @param Start_time - the time the process was initiate
     * @param Process_id - The PID of the process
     */
    void add_process(string Process_name, time_t Start_time, int Process_id, bool is_stop);

    /**
     * This method will remove the process (by process Id) from the jobs list
     * @param process_id
     * @return 0 - if the process was successfully remove from jobs
     *         (-1) - if the process is not on the jobs list
     */
    int process_remover(int process_id);

    /**
     * This method will search the process number listed on jobs based on the process id
     * @param process_id - the process identification number
     * @return  0 - the process number listed on jobs
     *          (-1)  - if the process is not listed on jobs
     */
    int Process_number(int process_id);

    /**
     * This method search the process id if in the jobs list
     * @param process_number - id of the process
     * @return Process id > 0
     *          -1 - if the the the number is not in the parameters of the list
     */
    int getPidByIndex(int process_number);



    /**
     * This method will return the number of process running on the background

     */
    int get_number_process();

	Process fg_proc;

    int firs_stop_process();
private:
    int child_status(int child_id);
    int zombie_kill();
    Process _process_running[100];
    string  _commands[50];
    int _number_of_commands;
    int _iterator;
    int _number_of_process;




};






#endif

