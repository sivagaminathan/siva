/* 
Author : SIVAGAMINATHAN SIVASANKARAN
FILENAME : upipe.c
DESCRIPTION : creates a parent and child processes that communiate a linux command sort test.txt | uniq via pipes. 
The sorted output is displayed in the screen
COURSE : CS 590 

*/



#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
int pipes[2];
pid_t pid;
FILE *stream;

int stat;
if(pipe(pipes) == -1)
    printf("could not create pipe\n");

// user fork() to create two processes 
switch(fork())
{
    case -1:
        fprintf(stderr, "error forking\n");
        break;
	
	// child process - does the sort function since it is executed first 
    case 0:
	// close the pipe from parent 
	close(pipes[0]);
	// use dup2 here for the pipes 
        dup2(pipes[1], 1);
	
	// get the pid of the child 
        pid = getpid();
        printf("Child, pid=%d\n", pid);
	//printf("\n Inside Case 0 \n");

	// use execlp to sort test.txt 
        execlp("sort", "sort","test.txt",(char*) NULL);
	perror("execl() failure! \n");
	// if execlp executes successfully, this statement will not be displayed - purely for debugging 
	printf("Failed i guess\n");

        break;
    default:
	// close pipe from child 
	close(pipes[1]);
	// open pipe for parent 
	dup2(pipes[0],0);
	//get parent pid 
        pid = getpid();
        printf("Parent, pid=%d\n", pid);
	//printf("\n Inside default \n");
        if(close(pipes[0]) == -1)
            printf("err closing read end pid=%d\n");

	// execlp to execute uniq command. 
	// The child already executes the sort test.txt 
	// this uniq command seemlessly executes as if its typed as a single command 
	// sort test.txt | uniq 
	execlp("uniq","uniq",(char*)NULL);
	break;
}
//wait 
wait(&stat);
return 0;
}
