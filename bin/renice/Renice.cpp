#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <Process.h>
#include "Renice.h"
#include "sys/renice.h" //work on this 


Renice::Renice(int argc, char** argv) : POSIXApplication(argc, argv)
{
	parser().setDescription("Output system process list");
   	parser().registerFlag('l', "list", "list priority level of processes");
	parser().registerPositional("PRIORITY", "Renice for the specified process till it finishes");
	parser().registerPositional("PID", "Wait for the ID process");
}

Renice::~Renice() 
{
	
}

Renice::Result Renice::exec()
{
    int pid = atoi(arguments().get("PID")); // Convert PID to int type
    Process::Priority priority = static_cast<Process::Priority>(atoi(arguments().get("PRIORITY")));
    
    // Check PID
    if (pid <= 0)
    {
        ERROR("PID is invalid `" << arguments().get("PID") << "'");
        return InvalidArgument;
    }
    
    if (priority < 1 || priority > 5) {
    	ERROR("priority is invalid");
    	return InvalidArgument;
    }
    
    // wait  
    if (renicepid(pid, priority) != pid)
    {
        ERROR("failed to wait: " << strerror(errno));
        return IOError;
    }

    return Success;
}
