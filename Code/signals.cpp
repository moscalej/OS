// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"
char* sigNumToName(int signum) {
	switch (signum) {
	case(1):	return "SIGHUP";
	case(2):	return "SIGINT";
	case(3):	return "SIGQUIT";
	case(4):	return "SIGILL";
	case(5):	return "SIGTRAP";
	case(6):	return "SIGABRT";
	case(7):	return "SIGBUS";
	case(8):	return "SIGFPE";
	case(9):	return "SIGKILL";
	case(10):	return "SIGUSR1";
	case(11):	return "SIGSEGV";
	case(12):	return "SIGUSR2";
	case(13):	return "SIGPIPE";
	case(14):	return "SIGALRM";
	case(15):	return "SIGTERM";
	case(17):	return "SIGCHLD";
	case(18):	return "SIGCONT";
	case(19):	return "SIGSTOP";
	case(20):	return "SIGTSTP";
	case(21):	return "SIGTTIN";
	case(22):	return "SIGTTOU";
	case(23):	return "SIGURG";
	case(24):	return "SIGXCPU";
	case(25):	return "SIGXFSZ";
	case(26):	return "SIGVTALRM";
	case(27):	return "SIGPROF";
	case(28):	return "SIGWINCH";
	case(29):	return "SIGIO";
	case(30):	return "SIGPWR";
	default: 	return NULL;
	}
	return NULL;
}


int SignalHandler::sendSig(int pID, int sigNum) {
    if (kill(pID,sigNum) == 0)
    {
		cout << "smash > signal ";
		cout << sigNumToName(sigNum);
		cout << " sent to pid ";
		cout << pID;
    } else
        cout<<"smash error: > signal not sent to pid ";
    return 0;
}

void SignalHandler::handleSIGTSTP()
{
	if (&jobs_and_history.fg_proc==NULL){
		return 0;
	}
	sendSig(jobs_and_history.fg_proc._process_id,20);
	jobs_and_history.fg_proc.is_stop = true;
	jobs_and_history.add_process(jobs_and_history.fg_proc._process_name,(int)jobs_and_history.fg_proc._time, jobs_and_history.fg_proc._process_id);
	&jobs_and_history.fg_proc=NULL;
	return 0;
}

void SignalHandler::handleSIGCHLD(siginfo_t* info) {
	pid_t pID = info->si_pid;
	pID = (int)pID;
	jobs_and_history.process_remover(pID);
	return 0;
}

void SignalHandler::handleSIGINT()
{
	if (jobs_and_history.fg_proc == NULL) {
		return 0;
	}
	sendSig(jobs_and_history.fg_proc._process_id, 2);
	&jobs_and_history.fg_proc = NULL;
	return 0;
}
