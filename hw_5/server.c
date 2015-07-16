/*

AUTHOR : SIVAGAMINATHAN SIVASANKARAN
COURSE : CS 590 
FILENAME : SERVER.C 

DESCRIPTION: GETS USER INPUT FROM CLIENT.C. TWO NUMBERS AND AN OPERATOR. PERFORMS THE OPERATION AS REQUESTED AND SENDS RESULTS TO CLIENT.C VIA PIPE. DISPLAY THE DATE RECEIVED ALONG WITH PID. 

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

// define pipes for read and write 
#define FIFO_I "inpipe"
#define FIFO_O "outpipe"
#define BUFFER_SIZE 100

int main()
{
	int pipe,res;
	char buffer[10];	
	float num1, num2;
	//contains the result 
	float num = 0.0;
	char c;
	
	// no need to mkfifo here, since client does it for us
	//res = mkfifo(FIFO_I,0777);	

	// open pipe in read only
	pipe = open(FIFO_O,O_RDONLY);
	
	if(pipe == -1)
	{
		printf("Error with pipe opening \n");
		exit(EXIT_FAILURE);
	}


	// read the input from client.c 
	res = read(pipe, &num1, BUFFER_SIZE);
	res = read(pipe, &num2, BUFFER_SIZE);
	//res = read(pipe, &c, BUFFER_SIZE);	
	
	printf("%f %f\n",num1,num2);
	close(pipe);
	// display pid 
	printf("Process B pid : %d \n", getpid());
	
	// reads the operator from client.c
	pipe = open(FIFO_O,O_RDONLY);
	res = read(pipe, &c, sizeof(c));

	close(pipe);

	// open pipe for write only mode 
	pipe = open(FIFO_O,O_WRONLY);
	if(pipe == -1)
		printf("Error opening pipe \n");
	// According to the operation required, send value to client.c 
	if(c =='+')
	{
		printf("Sending Sum of two numbers\n");
		num =num1+num2;
		res = write(pipe, &num,sizeof(num));
		if(res == -1)
			printf("Error res value \n");
	}
	else if(c =='-')
	{
		printf("Sending Subtraction of two numbers\n");
		num = num1-num2;
		res = write(pipe, &num,sizeof(num));
	}
	else if(c=='*')
	{
		
		printf("Sending Multiplication of two numbers\n");
		num = num1* num2;
		res = write(pipe, &num, sizeof(num));
	}
	else if(c=='/')
	{
		printf("Sending Divison of two numbers\n");
		if(num2 == 0)
		{
			printf("Divide by zero error\n");
			//close(pipe);
			//pipe = open (FIFO_O,O_WRONLY); 
			//res = write(pipe, "Divide by zero error", strlen("Divide by zero error"));
			//close(pipe);
			//pipe = open (FIFO_I,O_WRONLY);
		}
		else
			num = num1/num2;
		res = write(pipe, &num, sizeof(num)); 
		
	
	}
	else
		printf("Not a valid operator \n");
		
	close(pipe);
	return 0;
}

