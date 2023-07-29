#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	printf(".....test 3: parent process of a process tree.....\n");
	int pparent,pchild;//IDs
	pchild=fork();//create a child process
	if(pchild<0)
	{
		printf("process failed!\n");
		exit(1);
	}
	else if(pchild==0)
	{
		printf("Child process is created.\n");
		//the child process outputs the id of parent process every 2 seconds / 10 times
		for(int i=0;i<10;i++)
		{
			pparent=getppid();//get parent process id
			printf("Child process: PID of the parent process is %d.\n",pparent);
			sleep(2);
		}
	}
	else
	{
		//parent process outputs its id after 3 secs. process ends.
		printf("Parent process is about to end after 3 seconds.\n");
		sleep(3);
		printf("Parent process: PID of the parent process is %d. Process ends.\n",pparent);
	}
	printf(".....test 3 ends.....\n");//printf("PID=%d",pparent);

	return 0;
}

