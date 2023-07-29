#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/shm.h>//shared memory
#include<sys/stat.h>//shared memory
#include<time.h>
#include<math.h>//gcc -lm

#define KEY 75
#define SIZE 1024

int main()
{
	printf(".....test 4: shared memory - consumer.....\n");
	int shmidC;//id of shared memory
	char *shmaC;//address of shared memory
	int *ptrC;
	srand(time(NULL));
	
	shmidC=shmget(KEY,SIZE,0644|IPC_CREAT);//obtain access to shared memory
	if( (shmidC==-1 ) )
	{
		printf("shmget failed!\n");
		exit(1);
	}
	else
	{
		printf("shmget : returned %d.\n",shmidC);
	}

	shmaC=shmat(shmidC,0,0);//attach shared memory segments
	if( shmaC==(char*)-1 )
	{
		printf("shmat failed!\n");
		exit(1);
	}
	else
	{
		printf("shmat : returned %s with the address %p.\n",shmaC,shmaC);
	}

	printf("consumer outputs the squares of 10 integers produced by producer: ");
	ptrC=(int*)shmaC;
	for(int i=0;i<10;i++)
	{
		printf("%d ",(*ptrC)*(*ptrC));
		ptrC++;
	}printf("\n");
	printf("consumer outputs the roots of 10 integers produced by producer: ");
	ptrC=ptrC-10;
	for(int i=0;i<10;i++)
	{
		printf("%.2lf ",sqrt(*ptrC));
		ptrC++;
	}printf("\n");

	register int x;
	x=shmdt(shmaC);//detach shared memory segments
	if(x==-1)
	{
		printf("shmdt failed!\n");
		exit(1);
	}
	else
	{
		printf("shmdt : returned %d.\n",x);
	}

	int xx;
	xx=shmctl(shmidC,IPC_RMID,0);//remove shared memory segments
	if(xx==-1)
	{
		printf("shmctl failed!\n");
		exit(1);
	}
	else
	{
		printf("shmctl : returned %d.\n",xx);
	}

	printf(".....test 4 consumer ends.....\n");

	return 0;
}
