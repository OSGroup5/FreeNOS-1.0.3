#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <Process.h>
#include <ProcessClient.h>
#include "Kill.h"


Kill::Kill(int argc, char** argv) : POSIXApplication(argc, argv)
{
	parser().setDescription("Kill a background process.");
	parser().registerPositional("PROCESS", "The process id of a background process to kill.");
}

Kill::~Kill() 
{	
}

Kill::Result Kill::exec()
{
    // Get Process ID of a currently running process
    ProcessID pid = atoi(arguments().get("PROCESS"));

    ProcessCtl(pid, KillPID);

    // Done
    return Success;
}
