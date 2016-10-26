//
// Created by clay on 4/9/16.
//

#include "System.h"

pid_t System::fork(void)
{
    return fork();
}

int System::execvp(const char *file, char *const argv[])
{
    return execvp(file, argv);
}

pid_t System::waitpid(pid_t pid, int *status, int options)
{
    return waitpid(pid, status, options);
}

