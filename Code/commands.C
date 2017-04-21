//		commands.c
//********************************************
#include <sys/stat.h>
#include "commands.h"

//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
History smash_history;

int ExeCmd(void *jobs, char *lineSize, char *cmdString) {
    char *cmd;
    char *args[MAX_ARG];
    char pwd[MAX_LINE_SIZE];
    char *delimiters = (char*)" \t\n";
    int i = 0, num_arg = 0;


    bool illegal_cmd = false; // illegal command
    cmd = strtok(lineSize, delimiters);
    if (cmd == NULL)
        return 0;
    args[0] = cmd;
    for (i = 1; i < MAX_ARG; i++) {
        args[i] = strtok(NULL, delimiters);
        if (args[i] != NULL)
            num_arg++;

    }

/*************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/*************************************************/
//todo check what happend when we use cd ..
    if (!strcmp(cmd, "cd")) { //todo need to check the arguments
        if (num_arg < 2) {

            if (0 == chdir(args[1])) {
                getcwd(pwd, sizeof(pwd));
                cout << pwd << endl;

            } else {
                cout << args[0] << "- path not found" << endl;
            }
        } else{
            illegal_cmd = true;
        }

    }

        /*************************************************/
    else if (!strcmp(cmd, "pwd")) {
        if (num_arg == 0) {
            getcwd(pwd, sizeof(pwd));

            cout << pwd << endl;
        } else{
            illegal_cmd = true;
        }
    }

        /*************************************************/
    else if (!strcmp(cmd, "mkdir")) {

        if (num_arg < 2) {

            getcwd(pwd, sizeof(pwd));

            if (0 == mkdir(args[1], S_IRWXU)) {
                printf("new directory has been create");
            }
        }
    }
        /*************************************************/

    else if (!strcmp(cmd, "jobs")) {

    }
        /*************************************************/
    else if (!strcmp(cmd, "showpid")) {
        if(num_arg==0){
        cout<<getpid()<<endl;
            } else{
            illegal_cmd = true;
        }

    }
        /*************************************************/
    else if (!strcmp(cmd, "fg")) {

    }
        /*************************************************/
    else if (!strcmp(cmd, "bg")) {

    }
        /*************************************************/
    else if (!strcmp(cmd, "quit")) {

    }
        /*************************************************/
    else // external command
    {
        ExeExternal(args, cmdString);
        return 0;
    }
    if (illegal_cmd == true) {
        printf("smash error: > \"%s\"\n", cmdString);
        return 1;
    }

    smash_history.add_commands(args[0]);
    return 0;
}

//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char *cmdString) {
    int pID;
    switch (pID = fork()) {
        case -1:
            // Add your code here (error)

            /*
            your code
            */
        case 0 :
            // Child Process
            setpgrp();

            // Add your code here (execute an external command)

            /*
            your code
            */

        default:
            return;
            // Add your code here

            /*
            your code
            */
    }
}

//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char *lineSize) {
    char ExtCmd[MAX_LINE_SIZE + 2];
    char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) ||
        (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&"))) {
        // Add your code here (execute a complicated command)

        /*
        your code
        */
    }
    return -1;
}

//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char *lineSize, void *jobs) {

    char *Command;
    char *delimiters = (char *)" \t\n";
    char *args[MAX_ARG];
    if (lineSize[strlen(lineSize) - 2] == '&') {
        lineSize[strlen(lineSize) - 2] = '\0';
        // Add your code here (execute a in the background)

        /*
        your code
        */

    }
    return -1;
}
//Todo check if the history save the commands like it should do

/*This function will fill a char array with all the commands use until now
 * we will use this to print the History afterwards*/


void History::add_commands(string command) {

    if (_number_of_comands >= 50) {
        for (int i = 0; i < 50; ++i) {
            _commands[i] = _commands[i + 1];
        }
        _commands[50] = command;
    } else {
        _commands[_iterator] = command;
        _iterator++;
        _number_of_comands++;
    }


}


int History::add_proccess(char *process_name, char *args[]) {
    int process_id;
    fork();
    process_id = getpid();
    if (0 == process_id) {
        //child process
        execv(process_name, args);
    }


    return 0;
}
