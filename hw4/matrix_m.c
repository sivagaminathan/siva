#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct v
{
	int i;
	int j;

};


int a[100][100];
int b[100][100];
int c[100][100];
int k; 

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
/*

PRINTS MATRIX A FOR REFERENCE 
		for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                printf("%d\t", a[i][j]);
                        }
                        printf("\n");
                }
*/
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
		pthread_create(&tid[0],NULL,multiply,data);
			numberthreads++;
		}
	}
	for(j=0; j < numberthreads; j++)
    	{
            pthread_join( tid[j], NULL);
    	}
/*	
    //printf("A=\n");
	 for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                printf("%d\t", a[i][j]);
                        }
                        printf("\n");
                }

    printf("B=\n");

	for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                printf("%d\t", b[i][j]);
                        }
                        printf("\n");
                }
*/
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
