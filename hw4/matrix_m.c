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

#define M 3
#define N 3
#define d 2 

void multiply(void *data)
{
	
	int i = ((struct v*)data)->i;
	int j = ((struct v*)data)->j;
	int value=0;
	int x=0;
	int k;
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			value = 0;
			for(x= 0; x<d;x++)
			{
				value += a[i][x] * b [x][j];
			}
			c[i][j] = value;
			value = 0;
		}
	}
	pthread_exit(NULL);
}

int main()
{
	
	pthread_t tid[10000];

	int i,j,k;

	FILE *file;
        file = fopen ("matrix.dat","r");


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
		for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                printf("%d\t", a[i][j]);
                        }
                        printf("\n");
                }
		printf("\n\n\n\n\n\n");
		for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                fscanf(file,"%d", &b[i][j]);
                        }
                }
	}


	struct v *data = (struct v *)malloc(sizeof(struct v));
	data->i =0;
	data->j =0;
	
	int numberthreads = 0;	


	pthread_create(&tid[0],NULL,multiply,data);
	numberthreads++;

	for(j=0; j < numberthreads; j++)
    {
            pthread_join( tid[j], NULL);
    }

    printf("A=\n");
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

    printf("A*B=\n");
	
	for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                printf("%d\t", c[i][j]);
                        }
			printf("\n");
                }

    pthread_exit(NULL);

	return 0;
}
