#include "data.h"

#define MAXNUMSTUDENTS 3000

//define struct node with id and age
struct node
{
	int id;
  	int age;
};

//define struct set with NODE **student, count, length
struct set
{
	NODE **student;
  	int count;
  	int length;
};

/*
Arguments: int maxStudents
Return Type: SET*
Functionality: creates a set of 3,000 students and allocates memmory for each node in the array
O(n)
*/
SET* createDataSet(int maxStudents)
{
	SET *sp = malloc(sizeof(SET));
  	assert(sp != NULL);
  	sp->count = 0;//starts with no students in the class
  	sp->length = maxStudents;//class capped at 3000
  	sp->student = malloc(sizeof(NODE*)*maxStudents);//must allocate enough spots for the max number of students
  	assert(sp->student != NULL);
  	for(int i = 0; i < maxStudents; i++)
	{
    		sp->student[i] = malloc(sizeof(NODE));
    		assert(sp->student[i] != NULL);
  	}
  	return sp;
}
/*
Arguments: SET* sp
Return Type: void
Functionality: Free's each students info and the ADT
O(n)
*/
void destroyDataSet(SET* sp)
{
	assert(sp != NULL);
  	for(int i = 0; i < sp->length; i++)
	{
    		if(sp->student[i] == NULL)
		{
      			free(sp->student[i]);
    		}
  	}
  	free(sp->student);
  	free(sp);
  	return;
}

/*
Arguments: SET* sp, int matchID
Return Type: int
Functionality: searches for a students ID, if found the ID is returned, if not, returns -1
O(1)
*/
int searchID(SET* sp, int matchID)
{
	assert(sp != NULL);
  	printf("Searching for ID: %d\n", matchID);
  	if(sp->student[matchID]->id == matchID)
	{
    		return matchID;
  	}
  	return -1;
}

/*
Arguments: SET *sp, int insertID, int insertAge
Return Type: void
Functionality: inserts a new student to a certain spot with their own ID and age
O(1)
*/
void insertion(SET* sp, int insertID, int insertAge)
{
	assert(sp != NULL && sp->count < sp->length);
  	sp->student[insertID]->id = insertID;
  	sp->student[insertID]->age = insertAge;
  	printf("Student ID: %d, Age: %d\n", sp->student[insertID]->id, sp->student[insertID]->age);
  	sp->count++;
  	return;
}

/*
Arguments: SET* sp, int deleteID
Return Type: void
Functionality: searches for a certain student ID and then deleted that student from the list, as 
well as printing out the deleted student[s] info
O(1)
*/
void deletion(SET* sp, int deleteID)
{
	assert(sp != NULL);
  	int index = searchID(sp, deleteID);
  	if(index > 0)
	{
    		puts("The deleted student was found.");
    		printf("Deleted Student ID: %d, Age: %d\n", sp->student[index]->id, sp->student[index]->age);
    		free(sp->student[index]);
    		sp->count--;
  	}
  	else
	{
   	 	puts("No student was deleted.");
  	}
  	return;
}

