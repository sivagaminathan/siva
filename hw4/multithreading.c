#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>


void *print_hello(void *tid)
{
	printf("Hello World from thread %d\n",tid);
//	pthread_exit(NULL);
}

int main()
{
	pthread_t threads[9];
	int i, j, err=0;
	int ids[9];
	//err = pthread_create(&threads[1], NULL, print_hello, (void*)ids[1]);
	for(i=0;i<9;i++)
	{
		ids[i]=i;
		err = pthread_create(&threads[i],NULL,print_hello,(void*)ids[i]);
		if(err)
		{
			printf("Error %d\n",err);
			exit(1);
		}
	}
	printf("Hello\n");
	pthread_exit(NULL);
	//return 0;
}
