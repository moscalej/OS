// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"
SignalHandler sigHandler;
int SignalHandler::sendSig(int pID, int sigNum) {
    if (kill(pID,sigNum) == 0)
    {
        cout<<"smash > signal "sigNum" sent to pid "pID;
    } else
        cout<<"smash error: > signal not sent to pid ";
    return 0;
}
