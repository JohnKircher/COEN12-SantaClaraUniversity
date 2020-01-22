#include "data.h"

#define MAXNUMSTUDENTS 3000

//define struct student with next/prev pointers, age, and id
//O(1)
struct student
{
	STUDENT* next;
  	STUDENT* prev;
  	int age;
  	int id;
};

//define struct list with ageCount, and a head to the dummy node
//O(1)
struct list
{
	int ageCount;
  	STUDENT *head;
};

//define struct set with LIST **array, student count, and length
//O(1)
struct set
{
	LIST **array;
  	int studentCount;
  	int length;
};

/*
Arguments: int maxStudents
Return Type: SET*
Functionality: Creates the lists of ages for all the students, sets head pointers equal to itself and 
allocates memmory for each node
O(n)
*/
SET* createDataSet(int maxStudents)
{
	SET *sp = malloc(sizeof(SET));
  	assert(sp != NULL);
  	sp->studentCount = 0;
  	sp->length = MAXNUMSTUDENTS;
  	sp->array = malloc(sizeof(LIST*)*13);
  	for(int i = 0; i < 13; i++)
	{
    		sp->array[i] = malloc(sizeof(LIST));
    		sp->array[i]->head = malloc(sizeof(STUDENT));
    		assert(sp->array[i]->head != NULL);
    		sp->array[i]->head->next = sp->array[i]->head;
    		sp->array[i]->head->prev = sp->array[i]->head;
    		sp->array[i]->ageCount = 0;
  	}
  	return sp;
}

/*
Arguments: SET* sp
Return Type: void
Functionality: Deletes the list and free's all memory
O(n)
*/
void destroyDataSet(SET* sp)
{
	assert(sp != NULL);
  	for(int i=0; i < 13; i++)
	{
    		if(sp->array[i]->ageCount > 0)
		{
      			STUDENT* pDel;
      			STUDENT* pPrev = sp->array[i]->head->prev;
      			do{
        			pDel = pPrev;
        			pPrev = pDel->prev;
        			free(pDel);
      			}while(pDel != sp->array[i]->head);
    		}
    		free(sp->array[i]);
  	}
  	free(sp);
}

/*
Arguments: SET* sp, int matchAge
Return Type: int
Functionality: searches for a students age, if found, return 1, if not, return 0
O(1)
*/
int searchAge(SET* sp, int matchAge)
{
	assert(sp != NULL);
  	int index = matchAge - 18;
  	printf("------Searching for Age: %d-------\n", matchAge);
  	if(sp->array[index]->ageCount > 0)
	{
    		return 1;
  	}
  	return 0;
}

/*
Arguments: SET* sp, int insertID, int insertAge
Return Type: void
Functionality: allocates memory for the new node, then assigns the new node's data equal 
to the randomly generated ID and age. Then sets the new node to the ednd of the list and increases
the amount of students in the class 
O(1)
*/
void insertion(SET* sp, int insertID, int insertAge)
{
	assert(sp != NULL && sp->studentCount < sp->length);
  	STUDENT* addNode = malloc(sizeof(STUDENT));
  	assert(addNode != NULL);
  	int index = insertAge - 18;
  	addNode->id = insertID;
  	addNode->age = insertAge;
  	sp->array[index]->head->prev->next = addNode;
  	addNode->next = sp->array[index]->head;
  	addNode->prev = sp->array[index]->head->prev;
  	sp->array[index]->head->prev = addNode;
  	sp->array[index]->ageCount++;
  	printf("Student ID: %d, Age: %d\n", addNode->id, addNode->age);
  	sp->studentCount++;
  	return;
}
/*
Arguments: SET* sp, int deleteAge
Return Type: void
Functionality: searches for a certain node to delete, after deleting and printing the deleted node, 
then resets the head pointers and decreases the value of studentCount
O(n)
*/
void deletion(SET* sp, int deleteAge)
{
	assert(sp != NULL);
  	if(searchAge(sp, deleteAge) == 1)
	{
    		int index = deleteAge - 18;
    		puts("--------Student[s] found!!!--------");
    		int trials = 0;
    		STUDENT *printNode = sp->array[index]->head->next;
    		while(trials != sp->array[index]->ageCount) 
		{
      			printf("Deleted ID: %d Age: %d\n", printNode->id, printNode->age);
      			printNode = printNode->next;
      			trials++;
    		}
    		STUDENT* pDel = sp->array[index]->head->next;
    		while(pDel != sp->array[index]->head) 
		{
      			sp->array[index]->head->next = pDel->next;
      			free(pDel);
      			pDel = sp->array[index]->head->next;
      			sp->studentCount--;
    		}
    		sp->array[index]->ageCount = 0;
    		sp->array[index]->head->next = sp->array[index]->head;
    		sp->array[index]->head->prev = sp->array[index]->head;
  	}
}


/*
Arguments: SET* sp
Return Type: int
Functionality: starts from index and 0 and looks for a non-empty list, then increases min, 
then starts from the end of the array and looks for a non-empty list, then decreases max. 
Returns max - min
O(n)
*/
int maxAgeGap(SET* sp)
{
	assert(sp != NULL);
  	int min = 0;
  	int max = 12;
  	while(sp->array[min]->ageCount == 0)
	{
    		min++;
  	}
  	while(sp->array[max]->ageCount == 0)
	{
    		max--;
  	}
  	return (max - min);
}






