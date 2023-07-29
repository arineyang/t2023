#include <stdio.h>
#include <stdlib.h>

#define N 10	//max length of process name
#define MAX 100 //max capacity of processes
#define getpch(type) (type*)malloc(sizeof(type)) //getpch(type)
static int Time = 0;			//time counter of this expriment, initially 0
int TurnaroundTime[MAX] = { 0 };//a global array to record the turnaround time and calculate the average turnaround time at the end of experiment
int Timeflag = 0;				//a global variable to record the total count of information recorded in the array above

struct pcb				//struct
{
	char pname[N]; 		//process name
	int runtime;		//estimated running time
	int arrivetime;		//arrival time
	int priority;		//priority: the bigger number the higher priority
	char state; 		//process state: Waiting, Running, Blocked, Terminated
	struct pcb* next;	//pointer: address to the next pcb
	//.......
	int elapsedtime;	//elapsed running time

	int starttime;
	int finishtime;
	int turnaroundtime;
	float weightedturaroundtime;
	int firstflag;//0: never been run; 1: being re-running
}						//3 pcb pointer
*rhead = NULL,		//address of ready queue
* current,				//address of current running process
* bhead = NULL,//address of blocked queue
* thead = NULL;	//address of terminated queue
typedef struct pcb PCB;

PCB  *head_input;
PCB  *head_run;

void sort() //ready queue by priority
{
	PCB* first, * second;
	int jump = 0;	//mark whether there's a queue jump during sort()

	if ((rhead == NULL) || ((current->priority) > (rhead->priority)))//readyqueue is empty OR priority of current running process is bigger than any other process
	{
		//place current process on the head of ready queue
		current->next = rhead;
		rhead = current;
	}
	else
	{
		//get the first and second pcb of readyqueue
		first = rhead;
		second = first->next;
		
		while (second != NULL) //loop, until second=null
		{
			if ((current->priority) > (second->priority))
			{
				//put current between first and second
				current->next = second;
				first->next = current;

				second = NULL;	//(to end the loop)
				jump = 1;	//(queue jump occured)
			}
			else
			{
				first = first->next; second = second->next; //push first and second backwards
			}
		}
		
		if (jump == 0)
		{
			first->next = current; //place current after first (first is now the end of queue cause loop has already ended and there was no jump)
		}
	}
}

void inputprocess() //create process list
{
	int i, num;
	printf("\nPlease enter the number of your processes:");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		//scan the process information (user)
		printf("Please enter the basic information of Process %d\n", i + 1);
		current = getpch(PCB);
		printf("\tname of Process %d:", i + 1);
		scanf("%s", current->pname);
		printf("\tpriority of Process %d:", i + 1);
		scanf("%d", &current->priority);
		printf("\testimated running time of Process %d:", i + 1);
		scanf("%d", &current->runtime);
		
		//initialize the process and link it
		current->elapsedtime = 0;
		current->state = 'W';	//waiting
		current->next = NULL;	//cause the newest process is on the end of the list
		current->firstflag = 0; //never been run
		printf("Process %s has successfully created!\n", current->pname);
		printf("\n");
		sort();
	}
}

//functions to print information about processes
void printtitle()
{
	printf("Name\tStatus\tPriority\tRunning time\tElapsed time\n");
}
void printprocess(PCB* ptr)
{
	printf("%s\t", ptr->pname);
	printf("%c\t", ptr->state);
	printf("%d\t", ptr->priority); printf("\t");
	printf("%d\t", ptr->runtime); printf("\t");
	printf("%d\t", ptr->elapsedtime);
	printf("\n");
}
void printreadylist()	//print the ready list
{
	PCB* pr;
	pr = rhead;
	if (pr == NULL)//ready list is empty
	{
		printf("####### READY PROCESS: N/A #######\n");
	}
	else
	{
		printf("####### READY PROCESS QUEUE #######\n");
		printtitle();
		while (pr != NULL)//loop until the end
		{
			printprocess(pr);
			pr = pr->next;
		}
	}
}
void printblocklist()	//print the block list
{
	PCB* pb;
	pb = bhead;
	if (pb == NULL)//block list is empty
	{
		printf("####### BLOCKED PROCESS: N/A #######\n");
	}
	else
	{
		printf("####### BLOCKED PROCESS QUEUE #######\n");
		printtitle();
		while (pb != NULL)//loop until the end
		{
			printprocess(pb);
			pb = pb->next;
		}
	}
}
void printall()
{
	//printf("\n");
	printf("####### CURRENT RUNNING PROCESS - %s #######\n", current->pname);
	printtitle();
	printprocess(current);  //print current running process
	printreadylist();		//print ready list
	printblocklist();		//print block list
}
void printtime(PCB* x)//print process information with time's
{
	printtitle();
	printprocess(x);
	printf("  Turnaround time\t Weighted turnaround time\t\n");
	printf("  %d\t\t\t   %f\n", x->turnaroundtime, x->weightedturaroundtime);
}

void block() //block consecutive processes with the same priority in the readyqueue
{
	PCB* pb, * index = rhead;
	int count = 0; //block-able process: consecutive processes with the same priority in the readyqueue

	if (rhead == NULL) return; //ready queue is empty

	while ((index->next != NULL)) //loop until the end
	{
		if ((index->next->priority) >= rhead->priority)
		{
			index->next->state = 'B'; //state=block
			index = index->next;	  //index backwards
			count++;		  //count the blockable processes
		}
		else
		{
			break;
		}
	}

	if (count > 0)
	{
		//block the process
		pb = index->next;   //take out a sub-queue of equal-priority processes within the readyqueue
		index->next = bhead;//and put the sub-queue into head of blockqueue
		bhead = rhead->next;
		rhead->next = pb;   //and re-link the readyqueue
	}

}
void wakeup() //wake up the process with the most priority and least remaining running time in the blockqueue to be READY
{
	PCB* index, * prior, * t;		//index, prior, temp
	int exchange = 0;			//mark whether theres need to exchange the place
	if (bhead == NULL) return;		//blockqueue is empty

	if (bhead->next != NULL)		//blockqueue has more than one process
	{
		index = bhead->next;
		prior = bhead;
		
		while (index != NULL) //loop until the end
		{
			if ((index->priority) > (bhead->priority)) //criteria 1: biggest priority
			{
				exchange = 1;
			}
			else if ((index->priority) == (bhead->priority)) //criteria 2: least remaining running time
			{
				if ((index->runtime - index->elapsedtime) < (bhead->runtime - bhead->elapsedtime))
				{
					exchange = 1;
				}
			}

			if (exchange == 1)
			{
				//swap with first process in blockqueue
				prior->next = bhead;
				t = bhead->next;
				bhead->next = index->next;
				index->next = t;
				bhead = index;
				exchange = 0;
			}
			//put prior and index backwards
			prior = index;
			index = index->next;
		}
	}

	//place the first process in blockqueue to the firstplace in readyqueue
	t = bhead->next;
	bhead->next = rhead;
	rhead = bhead;
	bhead = t;
}
int listlength() //get the length of the process list
{
	int length = 0; PCB* pr = rhead;
	while (pr != NULL)
	{
		length++;
		pr = pr->next;
	}
	return length;
}
void destroy() //destroy current running process
{
	printf("Process %s is destroyed!\n", current->pname);
	free(current); //free memory of current running process
}
//void terminate();
//int   readyprocess( );

void runprocess() //运行进程的函数；
{
	(current->elapsedtime)++;

	if (current->elapsedtime == current->runtime) //process completed, so terminate it
	{
		current->state = 'C';	//set the process state to Completed
		current->finishtime = Time;	//set the time of termination
		current->turnaroundtime = current->finishtime - current->arrivetime;//calculate the turnaround time
		current->weightedturaroundtime = ((float)(current->turnaroundtime)) / ((float)(current->elapsedtime));//calculate the weighted turnaround time

		printf("Process %s is terminating...\n", current->pname);
		printtime(current);//print all the information before it gets destroyed

		//record the turnaround time information of the process into a global array
		TurnaroundTime[Timeflag] = current->turnaroundtime;
		Timeflag++;
		
		destroy();//free
	}
	else
	{
		(current->priority)--; //priority--: dynamic priority
		current->state = 'W';  //state=wait
		sort();
		if (bhead != NULL)	   //no process blocked
		{
			wakeup();
		}
		block();
	}
}



//main function
void main()
{
	//fp=open（"result.txt”, “w”）;
	
	inputprocess();
	int len = listlength();
	int round = 0;
	char ch;
	float totalturnaroundtime = 0.0, averageturnaroundtime;

	while ((len != 0) && (rhead != NULL))
	{
		ch = getchar();
		round++;
		printf("~~~~~ROUND %d~~~~~\n", round);

		//run the first process in the readyqueue
		current = rhead;
		rhead = current->next;
		current->next = NULL;
		current->state = 'R';

		//set start time
		if (current->firstflag == 0)
		{
			current->starttime = Time;
			current->firstflag = 1;
		}

		printall();	 //print all process information
		runprocess();//run
		Time++;		 //absolute time

		printf("Press any key to continue.....");
		ch = getchar();
		printf("\n");
	}
	printf("All the %d processes terminated. ", len);

	for (int i = 0; i < len; i++)
	{
		totalturnaroundtime += TurnaroundTime[i];
	}
	averageturnaroundtime = totalturnaroundtime / (float)len;
	printf("The average turnaround time = %f.\n", averageturnaroundtime);

	printf("\n.....EXPERIMENT 3 DONE.....Press any key to end.....\n");
	ch = getchar();
	return;
}
