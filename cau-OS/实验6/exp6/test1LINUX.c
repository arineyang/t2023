#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

#define N 10
struct Student
{
	char studentName[10];//name of the student, max length 10
	int studentNumber;//number of the student
	char studentClass[10];//class of the student
}student[N];

void studentW()
{
	//create a pointer to the file
	int myfile = open("studentII.dat", O_WRONLY | O_CREAT, 0600);
	assert(myfile != -1);//check if the file is opened successfully

	//write the file
	for (int i = 0; i < N; i++)
	{
		if (write(myfile, &student[i], sizeof(struct Student)) == -1)
		{
			printf("failed to write the file!\n");
		}
	}

	//close the file
	close(myfile);
}

void studentR()
{
	//input the information of 10 students
	printf("Please enter information of 10 students ~ \n");
	for (int i = 0; i < N; i++)
	{
		//input the information of 10 students
		printf("# Student %d \n", i + 1);
		printf("\tname: ");
		scanf("%s", student[i].studentName);
		printf("\tnumber: ");
		scanf("%d", &student[i].studentNumber);
		printf("\tclass: ");
		scanf("%s", student[i].studentClass);
	}
}

int main()
{
	studentR();//call the function to read from the keyboard
	studentW();//call the function to write into the file
	return 0;
}

