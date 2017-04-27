// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers
/*
 *
 */


/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */

#include "signals.h"

string SignalHandler::sigNumToName(int signum) {
    switch (signum) {
        case (1):
            return "SIGHUP";
        case (2):
            return "SIGINT";
        case (3):
            return "SIGQUIT";
        case (4):
            return "SIGILL";
        case (5):
            return "SIGTRAP";
        case (6):
            return "SIGABRT";
        case (7):
            return "SIGBUS";
        case (8):
            return "SIGFPE";
        case (9):
            return "SIGKILL";
        case (10):
            return "SIGUSR1";
        case (11):
            return "SIGSEGV";
        case (12):
            return "SIGUSR2";
        case (13):
            return "SIGPIPE";
        case (14):
            return "SIGALRM";
        case (15):
            return "SIGTERM";
        case (17):
            return "SIGCHLD";
        case (18):
            return "SIGCONT";
        case (19):
            return "SIGSTOP";
        case (20):
            return "SIGTSTP";
        case (21):
            return "SIGTTIN";
        case (22):
            return "SIGTTOU";
        case (23):
            return "SIGURG";
        case (24):
            return "SIGXCPU";
        case (25):
            return "SIGXFSZ";
        case (26):
            return "SIGVTALRM";
        case (27):
            return "SIGPROF";
        case (28):
            return "SIGWINCH";
        case (29):
            return "SIGIO";
        case (30):
            return "SIGPWR";
        default:
            return "\0";
    }

}


int SignalHandler::sendSig(int pID, int sigNum) {
    if (kill(pID, sigNum) == 0) {
        string temp;
        temp = sigNumToName(sigNum);
        cout << "smash > signal " << temp << " sent to pid " << pID << endl;
        return 1;
    } else
        cerr << "smash error: > signal not sent to pid " << endl;
    return 0;
}

/**
 * this handler is run by the child thats why we didnt have contrl of it
 * @param status
 */
void SignalHandler::handleSIGTSTP(int status) {


    if (jobs_and_history.fg_process._process_id == 0) {

        return;
    }



    this->jobs_and_history.add_process(this->jobs_and_history.fg_process._process_name,
                                       this->jobs_and_history.fg_process._time, this->jobs_and_history.fg_process._process_id,
                                       true);
    sendSig(jobs_and_history.fg_process._process_id, 20);
    jobs_and_history.fg_process._process_id = 0;



    return;
}

void SignalHandler::handleSIGCHLD(int parammeter, siginfo_t *info, void *function) {
    int result;
    pid_t pID = info->si_pid;
    waitpid(pID, &result, WUNTRACED);

    if (this->jobs_and_history.is_process_stop((int) pID) == false) {
        jobs_and_history.process_remover((int) pID);

        return;
    }
    return;
}

void SignalHandler::handleSIGINT(int status) {
    if (jobs_and_history.fg_process._process_id == 0) {
        return;
    }
    sendSig(jobs_and_history.fg_process._process_id, 2);
    jobs_and_history.fg_process._process_id = 0;
    return;
}
