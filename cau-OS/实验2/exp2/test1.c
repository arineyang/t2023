#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>//getpid()
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	printf(".....test 1: use fork() to create processes.....\n");
	int x=0;
	pid_t p1,p2,p3;//typedef //branch1:p1; branch2:p2,p3 (child process)
	p1=fork(); //create premier process (child process)
	if(p1<0)
	{
		printf("process1 failed!\n");
		exit(1);
	}
	else if(p1==0)
	{
		for(int i=0;i<4;i++)
		{
			printf("child1: (loop%d) pid=%d, x=%d.\n",i+1,getpid(),x);
			x+=2;
		}
	}
	else
	{
		p2=fork();//create second child process
		if(p2<0)
		{
			printf("process2 failed!\n");
			exit(1);
		}
		else if(p2==0)
		{
			p3=fork();//create third child process
			if(p3<0)
			{
				printf("process3 failed!\n");
				exit(1);
			}
			else if(p3==0)
			{
				for(int i=0;i<4;i++)
				{
					printf("child3: (loop%d) pid=%d, x=%d.\n",i+1,getpid(),x);
					x+=2;
				}
			}
			else
			{
				wait(NULL);
				for(int i=0;i<4;i++)
				{
					printf("child2: (loop%d) pid=%d, x=%d.\n",i+1,getpid(),x);
					x+=2;
				}
			}

		}
		else
		{
			int n=0,flag=0;
			while(n<2)
			{
				flag=waitpid(-1,NULL,0);
				if(flag>0)
				{
					n++;
				}
				for(int i=0;i<4;i++)
				{
					printf("myname: yangjijia; mynum: 2022308310229; parent: (loop%d), pid=%d, x=%d.\n",i+1,getpid(),x);
					x+=2;
				}
			}
		}

	}
	//printf("test 1 ends. input one char to stop the program.\n");
	//getchar();//stop the process from being exited

	return 0;
}
