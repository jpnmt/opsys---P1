#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main (int argc, char** argv) {

int n = 0; //Total child processes ever to launch
int s = 0; //maximum simultaneous child processes in the system
int m = 0; // total children launched so far 
int sc = 0; //current simutaneous children

int done = 0;


int opt;

while ((opt = getopt(argc, argv, "n:s:")) != -1) {
	switch(opt) {
		case 'n':
			n = atoi(optarg);
			if (n < 1 || n > 18) {
			    fprintf(stderr, "Error: -n value must be between 1 and 18\n");
		    	    exit(EXIT_FAILURE);		    
			}	
			break;
		case 's':
			s = atoi(optarg);
			if (s < 1 || s > 18) {
			    fprintf(stderr, "Error: -s value must be between 1 and 18\n");
		    	    exit(EXIT_FAILURE);		    
			}
			break;
		default:
			fprintf(stderr, "Usage: %s -n <n> -s <s>\n", argv[0]);
			exit(EXIT_FAILURE);
	}	

}
while (!done) {
	
	if (sc < s && m < n) { /*is the max child processes in the system is greater than those which are current 
				and total launched is greater than what has been launched so far */
		int c = fork(); //launch child
		if (c == 0) {
		char *args[] = {"./oss", "-n", argv[2], "-s", argv[4], NULL};	
		execvp(args[0], args);
		//printf(If you can read this, the Exec has failed\n);
		perror("execvp");
		exit(1);	
	}
	else { //parent
		sc++;
		m++;
	}	
    }

	if ( sc == 0 && m == n) { //no current chilren running and we ran all we wanted to from the beginning
		break;
	}

	if ( (sc == s && m < n) || (sc > 0 && m == n) ) { //if we are at our limit but we want to launch more/wait for a child to end
		wait(0);
		sc--;
	}



}
}
