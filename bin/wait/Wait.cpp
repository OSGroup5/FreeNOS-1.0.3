/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for particular process to finish execution.");
    parser().registerPositional("PROCESS", "Wait for the specified process.");
}

Wait::~Wait()
{
}


Wait::Result Wait::exec()
{
    pid_t proc = atoi(arguments().get("PROCESS"));
    int status;
    pid_t w;
    do {
        w = waitpid(proc, &status, 2|8);
        if (w == (pid_t) -1) {
            printf("Invalid process given.\n");
            break;
        }

        if ((status & 0x7f) == 0) {
            printf("process %d exited, status=%d\n", proc, ((status) & 0x7f));

        } else if ((((signed char) (((status) & 0x7f) + 1) >> 1) > 0) ) {
            printf("process %d killed (signal %d)\n", proc, ((status) & 0x7f));

        } else if ((((status) & 0xff) == 0x7f)) {
            printf("process %d stopped (signal %d)\n", proc, (((status) & 0xff00) >> 8));

        } else if ((status == 0xffff)) {
            printf("process %d continued\n", proc);
        } else {   
            printf("Unexpected status (0x%x)\n", status);
        }
    } while ( (status & 0x7f) != 0 && !(((signed char) (((status) & 0x7f) + 1) >> 1) > 0) );

    // Done
    return Success;
}
