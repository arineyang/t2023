
#include<stdio.h>
#include<stdlib.h> 

#define N 10

struct Student
{
	char studentName[10];//name of the student, max length 10
	int studentNumber;//number of the student
	char studentClass[10];//class of the student
}student[N];

int main()
{
	FILE* fp;//create a pointer to the file

	//open the file, if failed, return
	if ((fp = fopen("students.dat", "rb")) == NULL)
	{
		printf("fail to open the file!\n");
		exit(0);
	}

	//read the file and print the information of 10 students
	printf("The information of 10 students is as follows: \n");
	printf("\tName\t\tNumber\t\tClass\n");
	for (int i = 0; i < N; i++)
	{
		fread(&student[i], sizeof(struct Student), 1, fp);
		printf("\t%s\t\t%d\t\t%s\n", student[i].studentName, student[i].studentNumber, student[i].studentClass);
	}

	//close the file
	fclose(fp);
	printf("file reading completed!\n");

	return 0;
}
