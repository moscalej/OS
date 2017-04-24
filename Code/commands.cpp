//		commands.c
//********************************************
#include <sys/stat.h>
#include "commands.h"
#include "signals.h"



SignalHandler Handler;


/**
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************/
int ExeCmd(void *jobs, char *lineSize, char *cmdString) {
    char *cmd;
    char *args[MAX_ARG];
    char pwd[MAX_LINE_SIZE];
    char *delimiters = (char *) " \t\n";
    int i = 0, num_arg = 0;


	Handler.jobs_and_history.add_commands(lineSize);
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

/**
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
        } else {
            illegal_cmd = true;
        }

    }

        /*************************************************/
    else if (!strcmp(cmd, "pwd")) {
        if (num_arg == 0) {
            getcwd(pwd, sizeof(pwd));

            cout << pwd << endl;
        } else {
            illegal_cmd = true;
        }
    }
//todo also include the arguments
    else if (!strcmp(cmd, "history")) {
        if (num_arg == 0) {
            Handler.jobs_and_history.print_history();

        } else {
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
        //Todo need to debug and try
    else if (!strcmp(cmd, "jobs")) {
        if (num_arg == 0) {
            Handler.jobs_and_history.jobs();
        }

    }
        /*************************************************/
    else if (!strcmp(cmd, "showpid")) {
        if (num_arg == 0) {
            cout << "smash pid is " << getpid() << endl;
        } else {
            illegal_cmd = true;
        }

    }

        //Todo need to debug and try
        /*************************************************/
    else if (!strcmp(cmd, "fg")) {
        if (num_arg == 1) {//todo need to check is args[1] is also a number

            Handler.jobs_and_history.foreground(atoi(args[1]));
        }

    }
        /*************************************************/
    else if (!strcmp(cmd, "bg")) {
        Handler.jobs_and_history.background(atoi(args[1]));

    }
        /*************************************************/
//todo yonathan is in charge of this
    else if (!strcmp(cmd, "quit")) {
        if (num_arg == 0) {
            return Handler.sendSig(getpid(), 9);

        }

        else if (num_arg == 1 && args[1] == "kill") {
            for (int i = 0; i < Handler.jobs_and_history.get_number_process(); i++) {
                time_t start = time(NULL);
                while (difftime(time(NULL), start) <= 5 &&
                       Handler.sendSig(Handler.jobs_and_history.getPidByIndex(i), 15) != 0) {

                    if (difftime(time(NULL), start) > 5) {
                        Handler.sendSig(Handler.jobs_and_history.getPidByIndex(i), 9);
                    }
                }
                return Handler.sendSig(getpid(), 9);
            }


            illegal_cmd = true;
        }




    } else if (!strcmp(cmd, "kill")) {
        if (num_arg == 3) {
            char *sigNum;
            sigNum = strtok(args[1], "-");
            if (Handler.jobs_and_history.Process_number(atoi(args[2])))
                if (!Handler.sendSig(Handler.jobs_and_history.getPidByIndex(atoi(args[2])), atoi(sigNum)))
                    cout << "smash error : > kill job " <<args[2]<<" cannot send signal"<<endl;
                else
                    cout << "smash error: > kill job "<<args[2]<<" job does not exist"<<endl;
            else {
                cout << "smash error : > kill job "<<args[2]<<" cannot send signal"<<endl;
                illegal_cmd = true;
            }
        }
    }


        /*************************************************/
    else // external command
    {
        ExeExternal(args, cmdString);
        return 0;
    }
    if (illegal_cmd) {
        printf("smash error: > \"%s\"\n", cmdString);
        return 1;
    }

    return 0;
}

//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char *cmdString) {
    Handler.jobs_and_history.Start_process(cmdString, args);

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
// Description: this will check if the process nets to be run in the background
// Parameters: command string
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char *lineSize) {

    char *Command;
    char *delimiters = (char *) " \t\n";
    char *args[MAX_ARG];
    if (lineSize[strlen(lineSize) - 2] == '&') {
        lineSize[strlen(lineSize) - 2] = '\0';

        return 0;

    }
    return -1;
}
//Todo check if the history save the commands like it should do

/*This function will fill a char array with all the commands use until now
 * we will use this to print the Smash_handler afterwards*/


void Smash_handler::add_commands(string command) {

    if (_number_of_commands >= 50) {
        for (int i = 0; i < 50; ++i) {
            _commands[i] = _commands[i + 1];
        }
        _commands[50] = command;
    } else {
        _commands[_iterator] = command;
        _iterator++;
        _number_of_commands++;
    }
}

int Smash_handler::Start_process(char *line_size, char **args) {
    int pID;
    time_t start_time;
    time(&start_time);


    switch (pID = fork()) {
        case -1:
            perror("fail at creating the child process");

            return -1;
        case 0 :
            // Child Process
            if (setpgrp() == -1) perror("Fail to set the group id");

            execv(args[0], args); //here the program supouse to end

            perror("Error executing the program");
            return -1;
//todo check this part if bgcmd is -1 have to wait until end
        default:

            if (!BgCmd(line_size)) {
                add_process(args[0], (int) start_time, pID);
            } else {
                int status;
                int result = waitpid(pID, &status, WUNTRACED);
                if (result == -1) {
                    perror("something");
                    return -1;
                }
                fg_proc._process_name = args[0];
                fg_proc._process_id = pID;
                fg_proc._time = (int)start_time;
            }


    }

    return 0;
}

void Smash_handler::print_history() {
    for (int i = _number_of_commands; i > 0; --i) {
        cout << _commands[i - 1] << endl;
    }


}

int Smash_handler::jobs() {
    for (int i = 0; i < _number_of_process; ++i) {
        time_t time_running;
        time(&time_running);
        time_running = time_running -
                       _process_running[i]._time; //todo check is in the linux compiler time lib also works in sec

        cout << "[" << i << "] " << _process_running[i]._process_name\
         << " : " << _process_running[i]._process_id << " "\
        << time_running << " secs" << endl;
    }

    return 0;
}

//todo this functions need to be write i am jus leaving the base structure here
int Smash_handler::foreground(int place) {

    if (place == (-1)) {
        perror("this is an illigal place");
        return -1;


    } else if (place <= this->_number_of_commands){
        this->fg_proc = _process_running[place-1];

        for (int i = place; i <_number_of_commands ; ++i) {
            _process_running[i-1]=_process_running[i];

        }
        _number_of_process --;
        return 0;

    }

    perror("illegal place");
    return -1;
}
//todo solve this method
void Smash_handler::background(int place) {





}

void Smash_handler::add_process(char *Process_name, time_t Start_time, int Process_id) {
    if (this->_number_of_process >= 100) {
        for (int i = 0; i < 99; ++i) {
            _process_running[i] = _process_running[i + 1];
        }
        _process_running[99]._time = (int) Start_time;
        _process_running[99]._process_id = Process_id;
        _process_running[99]._process_name = Process_name;
    } else {
        _process_running[_number_of_process]._process_name = Process_name;
        _process_running[_number_of_process]._process_id = Process_id;
        _process_running[_number_of_process]._time = (int) Start_time;
        _number_of_process++;
    }

}

//todo check is this loop works
int Smash_handler::process_remover(int process_id) {
    for (int i = 0; i < _number_of_process; ++i) {

        if (process_id == _process_running[i]._process_id) {

            for (int j = i; j < _number_of_process; ++j) {
                _process_running[j] = _process_running[j + 1];
            }
            _number_of_process--;
            return 0;
        }
    }
    return -1;
}

int Smash_handler::Process_number(int process_id) {
    for (int i = 0; i < _number_of_process; ++i) {
        if (process_id == _process_running[i]._process_id) return i + 1;
    }
    perror("Problem in Smash handler::Process_number");
    return -1;
}

int Smash_handler::getPidByIndex(int process_number) {
    if (process_number < _number_of_process - 1 && process_number >= 0)
        return _process_running[process_number]._process_id;
    else
        return -1;


}

int Smash_handler::get_number_process() {

    return this->_number_of_process;
}


