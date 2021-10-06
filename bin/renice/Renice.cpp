#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <Process.h>
#include <ProcessManager.h>
//#include <sys/Renice.h>
#include "Renice.h"

Renice::Renice(int argc, char** argv) : POSIXApplication(argc, argv)
{
	parser().setDescription("Renice for particular process to finish execution.");
	parser().registerPositional("PROCESS", "Renice for the specified process till it finishes");
}

Renice::~Renice() 
{
	
}

Renice::Result Renice::exec() {
	ProcessID arg_id;
	int store_result, success;
	if ((arg_id = atoi(arguments().get("PROCESS"))) <= 4) 
	{
		ERROR("invalid PID`" << arguments().get("PROCESS") << "'");
		return InvalidArgument;
	}

	if (!success) {
		ERROR("failed to renice: " << arguments().get("PROCESS") << "'");
		return TimedOut;
	}
	return Success;
}
