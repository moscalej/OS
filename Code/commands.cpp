//		commands.c
//********************************************
#include <sys/stat.h>
#include "commands.h"
#include "signals.h"


/**
// function name: ExeCmd This funtion will be the main command traductor for the smash, also will be in charge
 //                of doing the basic commands: pwd, cd, showpid and mkdir (it was on the file so we write it)
//
// Parameters: Signal handler (this object is the main operator of our shell)
//                lineSize- is the raw command line
 //               cmdString - a better commmand string
// Returns: 0 - success,1 - failure
//**************************************************************************************/
int ExeCmd(char *lineSize, char *cmdString, SignalHandler &Handler) {
    char *cmd;
    char *args[MAX_ARG];
    char pwd[MAX_LINE_SIZE];
    char *delimiters = (char *) " \t\n";
    int num_arg = 0;

    Handler.jobs_and_history.add_commands(lineSize); //we Add the command to the history
    bool illegal_cmd = false;

    cmd = strtok(lineSize, delimiters);
    if (cmd == NULL)
        return 0;
    args[0] = cmd;
    for (int i = 1; i < MAX_ARG; i++) {
        args[i] = strtok(NULL, delimiters);
        if (args[i] != NULL)
            num_arg++;
    }

    if (!strcmp(cmd, "cd")) {
        if (num_arg < 2) {
            if (0 == chdir(args[1])) {
                getcwd(pwd, sizeof(pwd));
                cout << pwd << endl;
                return 0;
            }else if(args[1]=="-"){
                cout << pwd << endl;

            } else {
                cerr <<"Smash> "<< args[1] << " - path not found" << endl;
                return 1;
            }
        } else {
            illegal_cmd = true;
        }
    } else if (!strcmp(cmd, "pwd")) {
        if (num_arg == 0) {
            getcwd(pwd, sizeof(pwd));

            cout <<"Smash> "<< pwd << endl;
            return 0;
        } else {
            illegal_cmd = true;
        }
    } else if (!strcmp(cmd, "history")) {
        if (num_arg == 0) {
            Handler.jobs_and_history.print_history();
        } else {
            illegal_cmd = true;
        }
    } else if (!strcmp(cmd, "mkdir")) {
        if (num_arg < 2) {
            getcwd(pwd, sizeof(pwd));
            if (0 == mkdir(args[1], S_IRWXU)) {
                cout<<"Smash> "<<args[1] <<" directory has been create"<<endl;
                return 0;
            }
        }
    } else if (!strcmp(cmd, "jobs")) {
        if (num_arg == 0) {
            Handler.jobs_and_history.jobs();
        }
    } else if (!strcmp(cmd, "showpid")) {
        if (num_arg == 0) {
            cout << "Smash> pid is: " << getpid() << endl;
            return 0;
        } else {
            illegal_cmd = true;
        }
    } else if (!strcmp(cmd, "fg")) {
        if (num_arg == 1) {

            return Handler.jobs_and_history.foreground(atoi(args[1]));
        } else if (num_arg == 0) {
            return Handler.jobs_and_history.foreground(Handler.jobs_and_history.get_number_process());
        }else{ illegal_cmd = true;
        }

    } else if (!strcmp(cmd, "bg")) {
        int result;
        if (num_arg == 1) {
             return Handler.jobs_and_history.background(atoi(args[1]));
            return 0;
        } else if (num_arg == 0) {
            result = Handler.jobs_and_history.firs_stop_process();
            if (result != (-1)) {
               return Handler.jobs_and_history.background(result);
            }
        }else{
            illegal_cmd=true;
        }


    }

//todo yonathan is in charge of this
    else if (!strcmp(cmd, "quit")) {

        cout << "we are in quit with arg[1] = " << args[1] << endl;
        if (num_arg == 0) {
            return Handler.sendSig(getpid(), 9);

        } else if (num_arg == 1 && (string)args[1] == "kill") {

            cout << "we have to kill then all " << endl;
            for (int i = 1; i <= Handler.jobs_and_history.get_number_process(); i++) {

                Handler.sendSig(Handler.jobs_and_history.getPidByIndex(i), 15);
                Handler.jobs_and_history.set_settings(i, false);
            }

            time_t start;
            time(&start);
            time_t now_time;
            time(&now_time);

            while (true) {
                if ((abs((int)difftime(start, now_time))) > 5) break;
                if (Handler.jobs_and_history.get_number_process() == 0)break;
                time(&now_time);
                usleep(1000);
            }

            cout << "we pass 5 secs and there are process :" << Handler.jobs_and_history.get_number_process()
                 << "runing" << endl;
            if (Handler.jobs_and_history.get_number_process() > 0) {
                for (int j = 0; j < Handler.jobs_and_history.get_number_process(); ++j) {
                    Handler.sendSig(Handler.jobs_and_history.getPidByIndex(j), 9);

                }
            }

            return Handler.sendSig(getpid(), 9);


        }

        illegal_cmd = true;

    } else if (!strcmp(cmd, "kill")) {
        if (num_arg == 2) {
            char *sigNum;
            sigNum = strtok(args[1], "-");
            Handler.jobs_and_history.set_settings(atoi(args[2]), false);
            if (Handler.jobs_and_history.get_number_process() < (atoi(args[2]))) {
                cout << "smash error: > kill job " << args[2] << " job does not exist" << endl;
                return 0;
            }

            if (!Handler.sendSig(Handler.jobs_and_history.getPidByIndex(atoi(args[2])), atoi(sigNum))) {

                cout << "smash error : > kill job " << args[2] << " cannot send signal" << endl;
                return 0;
            }
        } else {
            illegal_cmd = true;

        }

    }
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
// Description: executes external command with the help of the Handler
// Parameters: external command arguments, Handler
// Returns: void
//**************************************************************************************
void ExeExternal(char *cmdString, char *args[20], SignalHandler &Handler) {
    Handler.jobs_and_history.Start_process(cmdString, args);

}

//**************************************************************************************
// function name: ExeComp
// Description: Checks if the external command is an expecial command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char *lineSize) {

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


    if (lineSize[strlen(lineSize) - 1] == '&') {
        lineSize[strlen(lineSize) - 1] = '\0';

        return 0;

    }
    return -1;
}

/*
 * we have the description of all this method in the interface
 */



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

            cerr << "Smash>> Fail at creating the child process" << endl;

            return -1;
        case 0 :
            // Child Process
            if (setpgrp() == -1) perror("Fail to set the group id");
            if (ExeComp(line_size) == 0) {
                char* csh=strdup("csh");
                char* f=strdup("-f");
                char* c = strdup("-c");
                char *arg[] = { csh, f,c, line_size, NULL };
                execvp(arg[0], arg);


            } else {

                execv(args[0], args);
            }
            perror("Error executing the program");
            return -1;

        default:

            if (BgCmd(line_size) == 0) {
                add_process(args[0], (int) start_time, pID, false);
                this->fg_process._process_id = 0;

            } else {
                int status;
                fg_process._process_name = args[0];
                this->fg_process._process_id = pID;
                fg_process._time = (int) start_time;
                fg_process.is_stop = false;

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

int Smash_handler::jobs() {
    for (int i = 0; i < _number_of_process; ++i) {

        time_t time_running;
        time(&time_running);
        time_running = time_running - _process_running[i]._time;
        string temp = (_process_running[i].is_stop) ? ("(Stopped)") : ("");
        cout << "[" << i + 1 << "] " << _process_running[i]._process_name\
 << " : " << _process_running[i]._process_id << " "\
 << time_running << " secs " << temp << endl;
    }

    return 0;
}

int Smash_handler::foreground(int place) {

    if (place == (-1)) {
        perror("this is an illigal place");
        return -1;


    } else if (place <= this->_number_of_process) {
        this->fg_process = _process_running[place - 1];

        if (this->process_remover(this->getPidByIndex(place)) == 0);
        {

            cout << "we got here and send the: " << fg_process._process_id << "(this is in fg comnadn )" << endl;

        }
        kill(this->fg_process._process_id, 18);
        fg_process.is_stop = false;
        int status;
        waitpid(fg_process._process_id, &status, WUNTRACED);
        return 0;
    }
    perror("illegal place");
    return -1;
}


int Smash_handler::background(int place) {
    if (place <= 0 || place > this->_number_of_process) {
        cerr << "Smash> This an illegal place" << endl;
        return -1;

    } else if (place <= this->_number_of_process) {
        kill(this->getPidByIndex(place), 18);
        this->set_settings(place, false);
        return 0;
    }

}

void Smash_handler::add_process(string Process_name, time_t Start_time, int Process_id, bool is_stop) {
    if (this->_number_of_process >= 100) {
        for (int i = 0; i < 99; ++i) {
            _process_running[i] = _process_running[i + 1];
        }
        _process_running[99]._time = (int) Start_time;
        _process_running[99]._process_id = Process_id;
        _process_running[99]._process_name = Process_name;
        _process_running[99].is_stop = is_stop;
    } else {
        _process_running[_number_of_process]._process_name = Process_name;
        _process_running[_number_of_process]._process_id = Process_id;
        _process_running[_number_of_process]._time = (int) Start_time;
        _process_running[_number_of_process].is_stop = is_stop;
        _number_of_process++;
        //debug cout<<"the "<<Process_name<<" procces was add: "<<_number_of_process<<endl;
    }

}

int Smash_handler::process_remover(int process_id) {
    for (int i = 0; i < _number_of_process; ++i) {

        if (process_id == _process_running[i]._process_id) {

            for (int j = i; j < _number_of_process - 1; ++j) {
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

    return -1;
}

int Smash_handler::getPidByIndex(int process_number) {
    if (process_number <= _number_of_process && process_number >= 0)
        return _process_running[process_number - 1]._process_id;
    else
        return -1;
}

int Smash_handler::get_number_process() {
    return this->_number_of_process;
}

Smash_handler::Smash_handler() {
    _number_of_process = 0;
    _iterator = 0;
    _number_of_commands = 0;
    fg_process._process_id = 0;
}

int Smash_handler::firs_stop_process() {
    for (int i = _number_of_process - 1; i >= 0; --i) {
        if (this->_process_running[i].is_stop) {
            return i + 1;
        }
    }
    return -1;

}

bool Smash_handler::is_process_stop(int pid) {
    int place = this->Process_number(pid);
    if (place == (-1)) return false;
    return _process_running[place - 1].is_stop;

}

void Smash_handler::set_settings(int place, bool is_stop) {
    if (place <= _number_of_process) {
        _process_running[place - 1].is_stop = is_stop;
    }

}


