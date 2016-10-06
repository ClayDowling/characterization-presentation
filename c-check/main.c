#include <stdlib.h>
#include <stdio.h>

#include "launch_program.h"

int main(int argc, char **argv)
{
	char * const params[] = {
		"vi",
		"launch_program.c",
		NULL
	};
	if (launch_program(".", "/usr/bin/vi", params)) {
		perror("launch_program");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
