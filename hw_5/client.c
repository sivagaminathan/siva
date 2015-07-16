/* 

AUTHOR : SIVAGAMINATHAN SIVASANKARAN 
FILENAME  : CLIENT.C 
COURSE : CS 590 
ASSIGNMENT 5 

DESCRIPTION : GETS 2 NUMBERS INPUT FROM USER ALONG WITH THE OPERATION NEEDED TO BE PERFORMED BETWEEN THE TWO NUMBERS. SENDS THE DATA TO SERVER.C VIA PIPE. AFTER SERVER.C SENDS RESULT, IT IS DISPLAYED ALONG WITH CLIENT PID. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

// Define two pipes .. input and output (read and write)
#define FIFO_I "inpipe"
#define FIFO_O "outpipe"
#define BUFFER_SIZE 10


int main()
{
	int pipe;
	int res;

	float num1,num2;
	char c;
	char buffer[30];
	
	// create the fifo pipes 
	res = mkfifo(FIFO_I,0777);
	res = mkfifo(FIFO_O,0666);
	if(res != 0)
	{
		printf("\n Could not create pipe \n");
		exit(EXIT_FAILURE);
	}
	

	// open in write only
	pipe = open(FIFO_O,O_WRONLY);

	// display the pid 
	printf("Process A pid : %d \n", getpid());
	
	// prompt user to input two numbers 
	printf("Please enter the two numbers : \n");
	scanf("%f%f",&num1,&num2);
	printf("Starting to write into pipe2\n");
	
	// prompt user to input the operator
	printf("Enter one of the operations '+' '-' '*' '/' \n");
	scanf("%c",&c);
	
	// write to the pipe the two number inputs 
	res = write(pipe,&num1,BUFFER_SIZE);
	res = write(pipe,&num2,BUFFER_SIZE);
	

	//res = write(pipe, &c, BUFFER_SIZE);
	
	if(res == -1)
	{
		printf("Res error\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		//res = write(pipe,c,BUFFER_SIZE);
	}
	
	//printf("Process %d finished\n",getpid());
	//close(res);
	close(pipe);
	
	// this is to open pipe to send the operator
	pipe = open(FIFO_O,O_WRONLY);
	
	printf("Enter Operator '+' '-' '*' '/' : ");
	scanf("%c",&c);

	// send the operator via this pipe 
	res = write(pipe, &c, sizeof(c));
	close(pipe);
	
	// open pipe in read only to receive from server
	pipe = open(FIFO_O,O_RDONLY);
	if(num2 == 0)
	{
		printf("Divide by zero error\n");
		//close(pipe);
		//pipe = (FIFO_I,O_RDONLY);
		//res = read(pipe, &buffer, sizeof(buffer));
		//close(pipe);
	}
	//pipe = open(FIFO_O,O_RDONLY);

	// read value from server and display
	res = read(pipe, &num1, sizeof(num1));

	printf("%f\n",num1);

	//exit(EXIT_SUCCESS);
	close(pipe);	
	return 0;
}
