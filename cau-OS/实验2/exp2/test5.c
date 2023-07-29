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
#include<sys/msg.h>//msg
#define KEY 75
#define SIZE 1024

struct message
{
	long messagetype;
	char messagetext[100];
}msg;

int main()
{
	printf(".....test 5: message queue.....\n");
	int shmid;//id of shared memory
	char *shma;//address of shared memory
	int *ptr;
	int num[10];
	int sum1=0,sum2=0,sum3=0;
	
	shmid=shmget(KEY,sizeof(int)*10,0644|IPC_CREAT);//obtain access to shared memory
	if(shmid==-1)
	{
		printf("shmget failed!\n");
		exit(1);
	}
	else
	{
		printf("shmget : returned %d.\n",shmid);
	}

	shma=shmat(shmid,NULL,0);//attach shared memory segments
	if( shma==(char*)-1 )
	{
		printf("shmat failed!\n");
		exit(1);
	}
	else
	{
		printf("shmat : returned %s with the address %p.\n",shma,shma);
	}

	printf("parent process : receiving input.\n");
	printf("please input 10 integers: ");
	ptr=(int*)shma;
	for(int i=0;i<10;i++)
	{
		scanf("%d",ptr);
		sum1=sum1+(*ptr);
		ptr++;
	}
	printf("the sum of the integers = %d.\n",sum1);

	printf("messaging from parent to child : creating a message queue\n");
	int mid=msgget(KEY+1,0777|IPC_CREAT);
	if(mid==-1)
	{
		printf("msgget failed!\n");
		exit(1);
	}
	else
	{
		printf("msgget : returned %d.\n",mid);
	}
	
	int cp=fork();
	if(cp==-1)
	{
		printf("fork failed!\n");
		exit(1);
	}
	else
	{
		printf("fork : returned %d. child process successfully created.\n",cp);
		if(cp==0) //entering child process
		{
			printf("child process : getting message\n");
			ptr=(int*)shma;
			for(int i=0;i<10;i++)
			{
				sum2=sum2+(*ptr)*(*ptr);
				ptr++;
			}
			printf("the sum of the squares of integers = %d.\n",sum2);

			printf("messaging from child to parent : creating a message queue\n");
			msg.messagetype=1;
			sprintf(msg.messagetext,"%d",sum2);
			int op=msgsnd(mid,&msg,100,0);//message send operations
			if(op==-1)
			{
				printf("msgsnd failed!\n");
				exit(1);
			}
			else
			{
				printf("msgsnd : returned %d.\n",op);
				//return 0;
			}
		}
		//else //parent process
		{
			printf("parent process.\n");
			//wait(NULL);//wait for the child being ended
			int r=msgrcv(mid,&msg,100,1,0);
			if(r==-1)
			{
				printf("msgrcv failed!\n");
				exit(1);
			}
			else
			{
				printf("msgrcv : returned %d.\n",r);
				sum3=sum1+atof(msg.messagetext);//from string to int
				printf("the sum of sum1 and sum2 = %d.\n",sum3);
			}
		}
	}


	int mctl=msgctl(mid,IPC_RMID,0);//message control operation
	if(mctl==-1)
	{
		printf("msgctl failed!\n");
		exit(1);
	}
	else
	{
		printf("msgctl : returned %d.\n",mctl);
	}

	register int x;
	x=shmdt(shma);//detach shared memory segments
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
	xx=shmctl(shmid,IPC_RMID,0);//remove shared memory segments
	if(xx==-1)
	{
		printf("shmctl failed!\n");
		exit(1);
	}
	else
	{
		printf("shmctl : returned %d.\n",xx);
	}

	printf(".....test 5 ends.....\n");

	return 0;
}
