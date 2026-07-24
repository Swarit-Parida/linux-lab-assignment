#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(){
	pid_t pid1, pid2;
	int status;

	pid1 = fork();

	if(pid1==0){
		printf("Child 1 (PID: %d) started.\n", getpid());
		sleep(3);
		printf("Child 1 finished.\n");
		exit(0);
	}

	pid2 = fork();

	if(pid2==0){
		printf("Child 2 (PID: %d) started.\n", getpid());
		printf("Child 2 is simulating an unresponsive process...\n");
		sleep(20);
		printf("Child 2 finished.\n");
		exit(0);
	}

	printf("Parent (PID: %d) monitoring child processes...\n", getpid());
	sleep(5);
	if(kill(pid2, 0) == 0){
		printf("Child 2 is still running. Sending SIGTERM...\n");
		kill(pid2, SIGTERM);
	}

	while(wait(&status) > 0);
	printf("All child processes completed.\n");
	return 0;
}
