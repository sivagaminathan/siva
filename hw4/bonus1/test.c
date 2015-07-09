
/*

 Sivagaminathan Sivasankaran 
 Homework 4 - Assignment CS 590
 Bonus PART 

 Matrix Multiplication using OPENMP 
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// TEST PRINT FUNCTION 
// NOT USED IN PROGRAM EXECUTION 
void print(int m[100][100],int num)
{
	int i,j;
	for(i=0;i<num;i++)
	{
		for(j=0;j<num;j++)
			printf("%d\t",m[i][j]);
		printf("\n");
	}
}

int main()
{
	
	int tid, nthreads, chunk;
	chunk = 10;

	int i,j,p;
	int a[100][100];
	int b[100][100];
	int c[100][100];
	
	int k=0;

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
		// FILL MATRIX B
		for(i=0;i<k;i++)
                {
                        for(j=0;j<k;j++)
                        {
                                fscanf(file,"%d", &b[i][j]);
                        }
                }

	}
	int num = k; // number of rows / column
	int NRA = k; // number of rows in Matrix A
	int NCB = k; // number of columns in Matrix B
	int NCA = k; // number of columns in Matrix A 

	/*** Parallel Threads using OPENMP ***/
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
{
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Using %d threads\n",nthreads);
    }

  // Matrix Multiplication happens in outer loop
  // Show Which Thread is doing which rows multiplications 
  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)    
    {
    printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<NCB; j++)       
      for (p=0; p<NCA; p++)
        c[i][j] += a[i][p] * b[p][j];
    }
  }   /*** End of parallel region ***/

/*** Print results ***/
printf("******************************************************\n");
printf("Result Matrix:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%d ", c[i][j]);
  printf("\n"); 
  }
printf("******************************************************\n");
printf ("Done.\n");

return 0;

}	


// CODE For OPENMP Reference Online // 
// ALL IMPLEMENTATIONS IN THE PROGRAM BELONG TO ME (Siva) // 

/*
	// PRINT RESULT MATRIX
	for(i=0;i<num;i++)
        {
                for(j=0;j<num;j++)
                        printf("%d\t",n[i][j]);
                printf("\n");
        }


	//print(m,k);
*/
