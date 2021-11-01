#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <Process.h>
#include <ProcessClient.h>
#include "Kill.h"

int processID;

Kill::Kill(int argc, char** argv) : POSIXApplication(argc, argv)
{
	parser().setDescription("Kill a background process.");
	parser().registerPositional("PROCESS", "The process id of a background process to kill.");
	processID =atoi(argv[1]);
}

Kill::~Kill() 
{	
}

Kill::Result Kill::exec()
{
   printf("processID = %d\n", processID);
   ProcessClient process;
   process.killProcess(processID);

    // Done
    return Success;
}
