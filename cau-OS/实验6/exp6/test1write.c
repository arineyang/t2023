#include<stdio.h>

#define N 10

struct Student
{
	char studentName[10];//name of the student, max length 10
	int studentNumber;//number of the student
	char studentClass[10];//class of the student
}student[N];

void mywrite()
{
	FILE* fp;//create a pointer to the file

	//open the file, if failed, return
	if ((fp = fopen("students.dat", "wb")) == NULL)
	{
		printf("failed to open the file!\n");
		return;
	}

	//write the file
	for (int i = 0; i < N; i++)
	{
		if (fwrite(&student[i], sizeof(struct Student), 1, fp) != 1)
		{
			printf("failed to write the file!\n");
		}
	}

	//close the file
	fclose(fp);
	printf("file writing completed!\n");
}

int main()
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
	mywrite();//call the function, to check if the file can be opened and written

	return 0;
}


