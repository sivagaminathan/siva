/*

Sivagaminathan Sivasankaran 
Assignment 4 CS 590 

Matrix Multiplicatin with multiple threads 

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to access arrays 
struct v
{
	int i;
	int j;

};

// global declarations 
int a[100][100];
int b[100][100];
int c[100][100];
int k; 


// The actual multiplication of rows and columns happen here 
void multiply(void *data)
{
	
	int i = ((struct v*)data)->i;
	int j = ((struct v*)data)->j;
	int value=0;
	int x=0;
	//int k;
	for(x= 0; x<k;x++)
	{
		// Actual multiplication of single row/column happens here 
		value += a[i][x] * b [x][j];
	//	printf("%d   %d ", a[i][x],b[x][j]);
	}
	// The multiplied value is then stored in array 
	//printf("   %d   \n",value);
	c[i][j] = value;
	//value = 0;
	//printf("%d  %d  %d\n",a[i][x],b[x][j],c[i][j]);	
	
	pthread_exit(NULL);
}

int main()
{
	// MAX number of Threads we can have 	
	pthread_t tid[10000];

	int i,j;

	FILE *file;
        file = fopen ("matrix.dat","r"); //file that contains the matrix


        // IF File does not exists 
        if(file == NULL)
        {
                printf("Error\n");
                //break;
        }
        // READ THE VALUE FOR NUMBER OF ROWS OR COLUMNS FROM FILE
        if ( fscanf(file,"%d",&k) > 0)
        {
                // FILL MATRIX A
                for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                fscanf(file,"%d", &a[i][j]);
                        }
		}


		// FILLS MATRIX B
		printf("\n");

		for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                fscanf(file,"%d", &b[i][j]);
                        }
                }
	}
	int numberthreads = 0;
	for(i=0;i<k;i++)
	{
		for(j=0;j<k;j++)
		{
		
		struct v *data = (struct v *)malloc(sizeof(struct v));
		data->i = i;
		data->j = j;

		// Create threads and keep count of number of threads created 
		pthread_create(&tid[0],NULL,multiply,data);
			numberthreads++;
		}
	}
	for(j=0; j < numberthreads; j++)
    	{
		// Use Thread join for all the threads 
            pthread_join( tid[j], NULL);
    	}


// Print the result matrix 
    printf("************************\n\n");
	printf("Result Matrix\n");
	
	for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                printf("%d\t", c[i][j]);
                        }
			printf("\n");
                }
	printf("************************\n\n");
    pthread_exit(NULL);

	return 0;
}
