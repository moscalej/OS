//		commands.c
//********************************************
#include <sys/stat.h>
#include "commands.h"
#include "signals.h"





/**
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************/
int ExeCmd(char *lineSize, char *cmdString, SignalHandler &Handler) {
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



    if (!strcmp(cmd, "cd")) {
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


    else if (!strcmp(cmd, "pwd")) {
        if (num_arg == 0) {
            getcwd(pwd, sizeof(pwd));

            cout << pwd << endl;
        } else {
            illegal_cmd = true;
        }
    }

    else if (!strcmp(cmd, "history")) {
        if (num_arg == 0) {
            Handler.jobs_and_history.print_history();

        } else {
            illegal_cmd = true;
        }

    }


    else if (!strcmp(cmd, "mkdir")) {

        if (num_arg < 2) {

            getcwd(pwd, sizeof(pwd));

            if (0 == mkdir(args[1], S_IRWXU)) {
                printf("new directory has been create");
            }
        }
    }

        //Todo need to debug and try
    else if (!strcmp(cmd, "jobs")) {
        cout <<"jobs1 with numargs: "<<num_arg<<endl;
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

    else if (!strcmp(cmd, "fg")) {
        if (num_arg == 1) {//todo need to check is args[1] is also a number

            Handler.jobs_and_history.foreground(atoi(args[1]));
        }
        else if(num_arg ==0){
            Handler.jobs_and_history.foreground(Handler.jobs_and_history.get_number_process());

        }

    }
        /*************************************************/
    else if (!strcmp(cmd, "bg")) {
        int result;
        if (num_arg == 1) {//todo need to check is args[1] is also a number

            Handler.jobs_and_history.background(atoi(args[1]));
        }
        else if(num_arg ==0){
            result = Handler.jobs_and_history.firs_stop_process();
            if(result != (-1)) {
                Handler.jobs_and_history.background(result);
            }
        }



    }
        /*************************************************/
//todo yonathan is in charge of this
    else if (!strcmp(cmd, "quit")) {
        if (num_arg == 0) {
            return Handler.sendSig(getpid(), 9);

        } else if (num_arg == 1 && args[1] == "kill") {
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
                    cout << "smash error : > kill job " << args[2] << " cannot send signal" << endl;
                else
                    cout << "smash error: > kill job " << args[2] << " job does not exist" << endl;
            else {
                cout << "smash error : > kill job " << args[2] << " cannot send signal" << endl;
                illegal_cmd = true;
            }
        }
    }


        /*************************************************/
    else // external command //
    {
        ExeExternal(cmdString, args, Handler);
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
void ExeExternal(char *cmdString, char *args[20], SignalHandler &Handler) {
    Handler.jobs_and_history.Start_process(cmdString, args);

}

//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char *lineSize) {//todo we need to see the way to use this it only returns -1(late version
    char ExtCmd[MAX_LINE_SIZE + 2];
    char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) ||
        (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&"))) {
        return 0;
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
    if (lineSize[strlen(lineSize) - 1] == '&') {
        lineSize[strlen(lineSize) - 1] = '\0';

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

    if (ExeComp(line_size)==0){
        args[0]=(char*) "csh";
        args[1]= (char*)"-f";
        args[2]= (char*)"-c";
        args[3]= line_size;
        for (int i = 4; i <20 ; ++i) {
            args[i]=NULL;
        }
    }

    switch (pID = fork()) {
        case -1:
            //todo writte a good coment
            cerr<<"fail at creating the child process"<<endl;

            return -1;
        case 0 :
            // Child Process
            if (setpgrp() == -1) perror("Fail to set the group id");

            execv(args[0], args);

            perror("Error executing the program");
            return -1;
//todo check this part if bgcmd is -1 have to wait until end
        default:

            if (BgCmd(line_size) == 0) {
                add_process(args[0], (int) start_time, pID, false);

            } else {
                int status;
                fg_proc._process_name = args[0];
                this->fg_proc._process_id = pID;
                fg_proc._time = (int) start_time;
                fg_proc.is_stop=false;

                int result = waitpid(pID, &status, WUNTRACED);

                //debug cout<<"we got control back"<<status<<endl;
                if (result == -1) {
                    perror("something");
                    return -1;
                }
            }
    }

    return 0;
}

void Smash_handler::print_history() {
    for (int i = 0; i < _number_of_commands - 1; ++i) {
        cout << _commands[i] << endl;
    }
}
//todo need to debug
int Smash_handler::jobs() {
    cout <<"number of process is: "<<_number_of_process<<endl;
    for (int i = 0; i < _number_of_process; ++i) {

        time_t time_running;
        time(&time_running);
        time_running = time_running - _process_running[i]._time;
        string temp= (_process_running[i].is_stop)?("(Stopped)"):("");
        cout << "[" << i+1 << "] " << _process_running[i]._process_name\
        << " : " << _process_running[i]._process_id << " "\
        << time_running << " secs " <<temp << endl;
    }

    return 0;
}

//todo this functions need to be write i am jus  the base structure here
int Smash_handler::foreground(int place) {

    if (place == (-1)) {
        perror("this is an illigal place");
        return -1;


    } else if (place <= this->_number_of_process) {
        this->fg_proc = _process_running[place - 1];

        this->process_remover(this->getPidByIndex(place));

        _number_of_process--;
        cout<<"we got here and send the: "<<fg_proc._process_id<<endl;
        kill(this->fg_proc._process_id,18);
        int status;
        waitpid(fg_proc._process_id, &status, WUNTRACED);
        return 0;
    }
    perror("illegal place");
    return -1;
}

//todo solve this method
void Smash_handler::background(int place) {
    if (place <= 0 || place >this->_number_of_process) {
        cerr<<"this is an illigal place"<<endl;//todo write a good comment

    } else if (place <= this->_number_of_process ) {

        kill(this->getPidByIndex(place),18);
        return ;
    }
    perror("illegal place");



}

void Smash_handler::add_process(string Process_name, time_t Start_time, int Process_id, bool is_stop) {
    if (this->_number_of_process >= 100) {
        for (int i = 0; i < 99; ++i) {
            _process_running[i] = _process_running[i + 1];
        }
        _process_running[99]._time = (int) Start_time;
        _process_running[99]._process_id = Process_id;
        _process_running[99]._process_name = Process_name;
        _process_running[99].is_stop=is_stop;
    } else {
        _process_running[_number_of_process]._process_name = Process_name;
        _process_running[_number_of_process]._process_id = Process_id;
        _process_running[_number_of_process]._time = (int) Start_time;
        _process_running[_number_of_process].is_stop=is_stop;
        _number_of_process++;
        //debug cout<<"the "<<Process_name<<" procces was add: "<<_number_of_process<<endl;
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

/**
 * This method will check if the
 * @param child_id
 * @return
 */
int Smash_handler::child_status(int child_id) {
    int status;
    pid_t return_pid = waitpid(child_id,&status,WNOHANG);
    if (return_pid == -1 )cout<<"there was an error checking the status of the child"<<endl;
    else if(return_pid==0){
        return 0;
    }
    else if(return_pid==child_id){
        return status;
    }
    return -2;


}

Smash_handler::Smash_handler() {
    _number_of_process=0;
    _iterator=0;
    _number_of_commands=0;
    fg_proc._process_id=0;

}

int Smash_handler::zombie_kill() {

    for (int i = 0; i < _number_of_process; ++i) {
       if( waitpid(_process_running[i]._process_id, NULL, WNOHANG) != 0){
           this->process_remover(_process_running[i]._process_id);
       }

    }

}

int Smash_handler::firs_stop_process() {
    for (int i = _number_of_process-1; i >=0; --i) {
        if (this->_process_running[i].is_stop){
            return i;

        }
    }
    return -1;

}


