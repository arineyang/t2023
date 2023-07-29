#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/shm.h>//shared memory
#include<sys/stat.h>//shared memory
#include<time.h>

#define KEY 75
#define SIZE 1024

int main()
{
	printf(".....test 4: shared memory - producer.....\n");
	int shmidP;//id of shared memory
	char *shmaP;//address of shared memory
	int *ptrP;
	srand(time(NULL));
	
	shmidP=shmget(KEY,SIZE,0644|IPC_CREAT);//obtain access to shared memory
	if( (shmidP==-1 ) )
	{
		printf("shmget failed!\n");
		exit(1);
	}
	else
	{
		printf("shmget : returned %d.\n",shmidP);
	}

	shmaP=shmat(shmidP,0,0);//attach shared memory segments
	if( shmaP==(char*)-1 )
	{
		printf("shmat failed!\n");
		exit(1);
	}
	else
	{
		printf("shmat : returned %s with the address %p.\n",shmaP,shmaP);
	}

	printf("producer produce 10 integers: ");
	ptrP=(int*)shmaP;
	for(int i=0;i<10;i++)
	{
		*ptrP=rand()%100;
		printf("%d ",*ptrP);
		ptrP++;
	}printf("\n");

	register int i;
	i=shmdt(shmaP);//detach shared memory segments
	if(i==-1)
	{
		printf("shmdt failed!\n");
	}
	else
	{
		printf("shmdt : returned %d.\n",i);
	}

	printf(".....test 4 producer ends.....\n");

	return 0;
}
