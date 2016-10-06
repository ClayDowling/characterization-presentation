#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int launch_program(const char *workingdir, const char *executable,
		char * const*argv)
{
	pid_t pid;
	int status;
	int died;

	switch(pid = fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		if (chdir(workingdir)) {
			perror(workingdir);
			exit(EXIT_FAILURE);
		}
		execvp(executable, argv);
	default:
		died = wait(&status);
		return status;
	}
}
