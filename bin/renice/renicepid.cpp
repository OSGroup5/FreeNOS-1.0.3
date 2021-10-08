#include <FreeNOS/User.h>
#include "sys/renicepid.h"
#include "sys/types.h"
#include <errno.h>

pid_t renicepid(pid_t pid, Process::Priority)
{
    const ulong result = (ulong) ProcessCtl(pid, Renice, priority);

    switch ((const API::Result) (result & 0xffff))
    {
        case API::NotFound:
            errno = ESRCH;
            return (pid_t) -1;

        case API::Success:
            
            return pid;

        default:
            errno = EIO;
            return (pid_t) -1;
    }
}
