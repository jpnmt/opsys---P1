#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv) {


	int IterNum = atoi(argv[1]);

	for (int i = 0; i < IterNum; i++) {
	printf(" USER PID: %d PPID %d Iteration %d before sleeping\n" , getpid(), getppid(), i+1);
	sleep(1);
	printf("---------------------------------------------------------\n");		
			}
	


	for (int i = 0; i < IterNum; i++) {
	printf(" USER PID: %d PPID %d Iteration %d after sleeping\n", getpid(), getppid(), i+1);
	}
	return EXIT_SUCCESS;	
			

}
