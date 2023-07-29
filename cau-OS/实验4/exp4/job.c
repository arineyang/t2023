#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#include<time.h>
#include "job.h"
int jobid = 0;
int siginfo = 1;
int fifo;
int globalfd;

struct waitqueue *head = NULL;
struct waitqueue *next = NULL, *current = NULL;

void schedule()
{
	struct jobinfo *newjob = NULL;
	struct jobcmd cmd;
	int count = 0;
	
	bzero(&cmd,DATALEN);
	if((count = read(fifo,&cmd,DATALEN))<0)
	err_sys("read fifo failed");
	
	#ifdef DEBUG
	 
	if(count){
		printf("cmd cmdtype\t%d\n"
			"cmd defpri\t%d\n"
			"cmd data\t%s\n",
			cmd.type, cmd.defpri, cmd.data);
	} else
	printf("no data read\n");
	#endif
	switch(cmd.type){
		case ENQ:
			do_enq(newjob,cmd);
			break;
		case DEQ:
			do_deq(cmd);
			break;
		case STAT:
			do_stat(cmd);
			break;
		default:
			break;
	}
/*更新等待队列中的作业*/
	updateall();
	/*选择高优先级作业*/
	next = jobselect();
/*作业切换*/
	jobswitch();
}
int allocjid()
{
	return ++jobid;
}
void updateall()
{
	struct waitqueue *p;
/*更新作业运行时间*/
	if(current)
		current->job->run_time += 1;
/*更新作业等待时间*/
	for(p=head;p!=NULL;p=p->next){
		p->job->wait_time += 100;
		if(p->job->wait_time>=1000&&p->job->curpri<3)
			p->job->curpri++;
	}
}

struct waitqueue* jobselect()
{
	struct waitqueue *p,*prev,*select,*selectprev;
	int highest = -1;
	select = NULL;
	selectprev = NULL;
	if(head){
		for(prev = head,p=head;p!=NULL;prev = p,p=p->next)
			if(p->job->curpri>highest){
				select = p;
				selectprev = prev;
				highest = p->job->curpri;
			} 
			selectprev->next = select->next;
			if(select == selectprev)
				head = NULL;
	}
	return select;
}

void jobswitch()
{
	struct waitqueue *p;
	int i;
	if(current && current->job->state ==DONE){/*当前作业完成*/
/*作业完成，删除它*/
		for(i=0;(current->job->cmdarg)[i]!=NULL;i++){
			free((current->job->cmdarg[i]));
			(current->job->cmdarg)[i] = NULL;
		}
		free(current->job->cmdarg);
		free(current->job);
		free(current);
	}
	if(next == NULL&&current == NULL)/*没有作业要运行*/
		return;
	else if(next!=NULL&&current==NULL){/*开始新的作业*/
		printf("begin start new job\n");
		current = next;
		next = NULL;
		current->job->state = RUNNING;
		kill(current->job->pid,SIGCONT);
		return;
	} else if(next!=NULL&&current!=NULL){/*切换作业*/
		printf("begin switch\n");
		kill(current->job->pid,SIGSTOP);
		current->job->curpri = current->job->defpri;
		current->job->wait_time = 0;
		current->job->state = READY;
/*放回等待队列*/
		if(head){
			for(p=head;p->next!=NULL;p=p->next);
			p->next = current;
		}
		else{/*next == NULL且current！=NULL，不切换*/
			head = current;
		}
		current = next;
		next = NULL;
		current->job->state=RUNNING;
		kill(current->job->pid,SIGCONT);
		return;
	}
}
void sig_handler(int sig,siginfo_t *info,void *notused)
{
	int status;
	int ret;
	
	switch(sig){
		case SIGVTALRM:
			schedule();
			return;
		case SIGCHLD:
			ret = waitpid(-1,&status,WNOHANG);
			if(ret == 0)
			return;
			if(WIFEXITED(status)){
				current->job->state = DONE;
				printf("normal termation, exit status = %d\n",WEXITSTATUS(status));
			}else if(WIFSIGNALED(status)){
				printf("abnormal termation, signal number = %d\n",WTERMSIG(status));
			}else if(WIFSTOPPED(status)){
				printf("child stopped, signal number = %d\n",WSTOPSIG(status));
			}
			return;
		default:
			return;
	}
}
void do_enq(struct jobinfo *newjob,struct jobcmd enqcmd)
{
	struct waitqueue *newnode,*p;
	int i=0,pid;
	char *offset,*argvec,*q;
	char **arglist;
	sigset_t zeromask;
	
	sigemptyset(&zeromask);
/*填满jobinfo数据结构*/	
	newjob = (struct jobinfo *) malloc(sizeof(struct jobinfo));
	newjob->jid = allocjid();
	newjob->defpri = enqcmd.defpri;
	newjob->curpri = enqcmd.defpri;
	newjob->ownerid = enqcmd.owner;
	newjob->state = READY;
	newjob->create_time = time(NULL);
	newjob->wait_time = 0;
	newjob->run_time = 0;
	arglist = (char**) malloc(sizeof(char*)*(enqcmd.argnum+1));
	newjob->cmdarg = arglist;
	offset = enqcmd.data;
	argvec = enqcmd.data;
while(i<enqcmd.argnum){
		if(*offset==':'){
			*offset++='\0';
			q = (char*) malloc(offset - argvec);
			strcpy(q,argvec);
			arglist[i++] = q;
			argvec = offset;
		}else
			offset++;
	}
	arglist[i] = NULL;
	#ifdef DEBUG
	printf("enqcmd argnum %d\n",enqcmd.argnum);
	for(i = 0;i<enqcmd.argnum;i++)
		printf("parse enqcmd:%s\n",arglist[i]);
	
	#endif
/*向等待队列中增加新的作业*/
	newnode = (struct waitqueue*) malloc(sizeof(struct waitqueue));
	newnode->next = NULL;
	newnode->job = newjob;
	
	if(head){
		for(p = head;p->next!=NULL;p=p->next)
		p->next = newnode;
	} else
		head = newnode;
	/*为作业创建进程*/
	if((pid = fork())<0)
		err_sys("enq fork failed");
/*子进程*/
	if(pid==0){
		newjob->pid = getpid();
/*阻塞子进程，等待执行*/
		raise(SIGSTOP);
	#ifdef DEBUG
		printf("begin running\n");
		for(i=0;arglist[i]!=NULL;i++)
			printf("arglist %s\n",arglist[i]);
	#endif
/*复制文件描述符到标准输出*/
		dup2(globalfd,1);
		if(execv(arglist[0],arglist)<0)
			printf("exec failed\n");
		exit(1);
	}else{
		newjob->pid = pid;
	}
}
void do_deq(struct jobcmd deqcmd)
{
	int deqid,i;
	struct waitqueue *p,*prev,*select,*selectprev;
	deqid = atoi(deqcmd.data);
	#ifdef DEBUG
	printf("deq jid %d\n",deqid);
	#endif
	/*current jobid == deqid，终止当前作业*/
	if(current && current->job->jid == deqid){
		printf("terminate current job\n");
		kill(SIGKILL,current->job->pid);
		for(i=0;(current->job->cmdarg)[i]!=NULL;i++){
			free((current->job->cmdarg)[i]);
			(current->job->cmdarg)[i] = NULL;
		}
		free(current->job->cmdarg);
		free(current->job);
		free(current);
		current = NULL;
	}else{/*或者在出队的ID在等待队列中查找它*/
		select = NULL;
		selectprev = NULL;
		if(head){
			for(prev = head,p=head;p!=NULL;prev = p,p = p->next)
				if(p->job->jid == deqid){
					select = p;
					selectprev = prev;
					break;
				}
			    selectprev->next = select->next;
			    if(select == selectprev)
		head = NULL;
		}
		if(select){
			for(i=0;(select->job->cmdarg)[i]!=NULL;i++){
				free((select->job->cmdarg)[i]);
				(select->job->cmdarg)[i] = NULL;
			}
			free(select->job->cmdarg);
			free(select->job);
			free(select);
			select = NULL;
		}
	}
}
void do_stat(struct jobcmd statcmd)
{
	struct waitqueue *p;
	char timebuf[BUFLEN];
/*
*打印所有作业的统计信息：
*1.作业ID
*2.进程ID
*3.作业所有者
*4.作业运行时间
*5.作业等待时间
*6.作业创建时间
*7.作业状态
*/
/*打印头部信息*/
	printf("JOBID\tPID\tOWNER\tRUNTIME\tWAITTIME\tCREATTIME\t\tSTATE\n");
	if(current){
		strcpy(timebuf,ctime(&(current->job->create_time)));
		timebuf[strlen(timebuf)-1] = '\0';
		
		printf("%d\t%d\t%d\t%d\t%d\t%s\t%s\n",
			current->job->jid,
			current->job->pid,
			current->job->ownerid,
			current->job->run_time,
			current->job->wait_time,
			timebuf,
			"RUNNING");
	}
	for(p=head;p!=NULL;p=p->next){
		strcpy(timebuf,ctime(&(p->job->create_time)));
		timebuf[strlen(timebuf)-1]='\0';
		
		printf("%d\t%d\t%d\t%d\t%d\t%s\t%s\n",
			current->job->jid,
			current->job->pid,
			current->job->ownerid,
			current->job->run_time,
			current->job->wait_time,
			timebuf,
			"READY");
	}
}

int main()
{
	struct timeval interval;
	struct itimerval new,old;
	struct stat statbuf;
	struct sigaction newact,oldact1,oldact2;
	if(stat("/tmp/server",&statbuf)==0){
/*如果fifo文件存在，删掉*/
		if(remove("/tmp/server")<0)
			err_sys("remove failed");
	}
	if(mkfifo("/tmp/server",0666)<0)
		err_sys("mkfifo failed");
	/*在非阻塞模式下打开fifo*/
	if((fifo=open("/tmp/server",O_RDONLY|O_NONBLOCK))<0)
		err_sys("open fifo failed");
/*为作业输出打开文件描述符*/
	if((globalfd = open("/dev/null",O_WRONLY))<0)
		err_sys("open global file failed");
	/*建立信号处理函数*/
	newact.sa_sigaction = sig_handler;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = SA_SIGINFO;
	
	sigaction(SIGCHLD,&newact,&oldact1);
	sigaction(SIGVTALRM,&newact,&oldact2);
	/*设置时间间隔为100毫秒*/
	interval.tv_sec = 0;
	interval.tv_usec = 100;
	
	new.it_interval = interval;
	new.it_value = interval;
	setitimer(ITIMER_VIRTUAL,&new,&old);
	while(siginfo == 1);
	close(fifo);
	close(globalfd);
	return 0;
}


    
