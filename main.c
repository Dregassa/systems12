#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

char child_process(){ // 1 byte of space for nap_time
	int pid = getpid();

	srand(pid); //srand(time(NULL)) was causing problems
	char nap_time = (rand() % 16) + 5; //[5,20]
	
	printf("(PID=%d): NOOOOO!!!\n", pid);
	sleep(nap_time);
	printf("(PID=%d): Done laboring after sleeping %d seconds\n", pid, nap_time);
	return nap_time;

}

int main(){
	int pid = getpid();
	printf("(PID=%d): I am your father\n", pid);
	int f = fork();

	if (f == -1){
		printf("First fork failed: Exiting program\n");
		exit(1);
	}

	else if (f){
		f = fork();
	}

	if (f == -1){
		printf("Second fork failed: Exiting program\n");
		exit(2);
	}
	
	else if (f){//parent
		int status;
		int first_child = wait( &status );
		if (first_child != -1){
			char time_slept = (char) WEXITSTATUS(status); 
			printf("(PID=%d): Child (PID = %d) slept %d seconds\n",pid, first_child, time_slept);
		}
		else{
			printf("%s\n", strerror(errno));
		}
	}
	else{ //children
		return child_process();	
	}

	return 0;
	
}
