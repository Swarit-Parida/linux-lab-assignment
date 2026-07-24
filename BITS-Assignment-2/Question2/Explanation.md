# Question 2 – Process Management

## Command 1 – Write the C program

Command:
vi process_manager.c

Program content:

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


Explanation:
The parent creates two child processes using fork(). Child 1 simulates a normal, responsive process 
— it sleeps for 3 seconds and then exits. Child 2 simulates an unresponsive 
process by sleeping for 20 seconds, much longer than the parent is 
willing to wait. The parent monitors both children by sleeping for 5 
seconds, then uses kill(pid2, 0) to check whether Child 2 is still 
running — sending signal 0 doesn't actually terminate a process, it 
only checks if the PID still exists. Since Child 2 is still asleep at 
this point, the parent sends it SIGTERM to terminate it. Finally, the 
parent calls wait() in a loop until it returns -1 (no more children 
left), which collects the exit status of both children — this is what 
prevents zombie processes, since a zombie only exists when a child has 
exited but its parent hasn't yet called wait() to read its status.

---

## Command 2 – Compile the program

Command:
gcc process_manager.c -o process_manager

Explanation:
Compiles the C source code into an executable named process_manager. 
No errors during compilation confirms the code is syntactically correct.

---

## Command 3 – Run the program

Command:
./process_manager

Output: Parent (PID: 24623) monitoring child processes...
        Child 2 (PID: 24625) started.
        Child 2 is simulating an unresponsive process...
        Child 1 (PID: 24624) started.
        Child 1 finished.
        Child 2 is still running. Sending SIGTERM...
        All child processes completed.

Explanation:
Executes the program. It spawns 2 child processes — Child 1 finishes 
normally within 3 seconds, while Child 2 simulates an unresponsive 
process. After monitoring for 5 seconds, the parent detects Child 2 
is still running and sends it SIGTERM. The program then waits for 
both children to be fully reaped, leaving no zombie processes behind.

---

## Command 4 – Verify no zombie processes remain

Command:
ps aux | grep defunct

Output: codespa+   28532  0.0  0.0   7080  2340 pts/0    S+   05:19   0:00 grep --color=auto defunct

Explanation:
Only the grep command itself appears (self-match), confirming no real 
zombie processes remain after wait() reaped both children.

---

## Command 5 – Verify files created

Command:
ls -l

Output: total 24
        -rw-rw-rw-  1 codespace codespace     0 Jul 24 03:42 Explanation.md
        -rwxrwxrwx  1 codespace codespace 16312 Jul 24 05:10 process_manager
        -rw-rw-rw-  1 codespace codespace   777 Jul 24 05:10 process_manager.c
        drwxrwxrwx+ 2 codespace codespace  4096 Jul 24 03:42 screenshots

Explanation:
Lists the files in the current directory, confirming that both the 
source file (process_manager.c) and the compiled executable 
(process_manager) exist.

---
