// Wrapper class for posix system interface, so that it can be mocked out in tests.
//
// Created by clay on 4/9/16.
//

#ifndef NEWANIMAL_SYSTEM_H
#define NEWANIMAL_SYSTEM_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

class SystemInterface {
public:

    // Process control functions
    virtual pid_t fork(void) = 0;
    virtual int execvp(const char *file, char *const argv[]) = 0;
    virtual pid_t waitpid(pid_t pid, int *status, int options) = 0;
};

class System : public SystemInterface {
public:

    // Process control functions
    virtual pid_t fork(void);
    virtual int execvp(const char *file, char *const argv[]);
    virtual pid_t waitpid(pid_t pid, int *status, int options);
};


#endif //NEWANIMAL_SYSTEM_H
