//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define REMOVED 2

static int partition(void **elts, int low, int high, int (*compare)());
static void quicksort(void **elts, int low, int high, int (*compare)());
static int search(SET *sp, void *elt, bool *find);

//define structure
struct set
{
	void** data;
  	char* flag;
  	int length;
  	int count;
  	int (*compare)();
  	unsigned (*hash)();
};

/*
Arguments: SET *sp, void *elt, bool *find
Return Type: int
Functionality: Returns the location of an element in the array
Big-O: O(n)
*/
static int search(SET *sp, void *elt, bool* find)
{
	assert(sp != NULL && elt != NULL);
  	int index = (*sp->hash)(elt) % sp->length;
  	int trials = 0;
  	int deletedSlot = -1;
  	while(trials < sp->length)
	{
    		if(sp->flag[index] == EMPTY)
		{
      			*find = false;
      			return deletedSlot != -1 ? deletedSlot : index;
    		}
    		else if(sp->flag[index] == REMOVED)
		{
      			trials++;
      			if(deletedSlot == -1)
			{
				deletedSlot = index;
      			}
      			index = (index + 1) % sp->length;
    		}
    		else
		{
      			if((*sp->compare)(sp->data[index], elt) == 0)
			{ 
				*find = true;
				return index; 
      			}
      			else
			{ 
				index = (index + 1) % sp->length;
				trials++;
      			}
    		}
  	}
  	*find = false;
  	return deletedSlot;
}



/*
Arguments: int maxElts, int (*compare)(), unsigned (*hash)()
Return Type: SET*
Functionality: Creates the set
Big-O: O(n)
*/
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
	SET *sp = (SET*)malloc(sizeof(SET));
  	assert(sp != NULL);
  	sp->count = 0;
  	sp->length = maxElts;
  	sp->compare = compare;
  	sp->hash = hash;
  	sp->data = malloc(sizeof(void*)*maxElts);
  	sp->flag = (char*)malloc(sizeof(char)*maxElts);
  	assert(sp->data != NULL && sp->flag != NULL);
  	for(int i = 0; i < sp->length; i++)
  	{
    		sp->flag[i] = EMPTY;
 	}
  	return sp;
}

/*
Arguments: SET *sp
Return Type: void
Functionality: Destroys the set
Big-O: O(n)
*/
void destroySet(SET *sp)
{
	assert(sp != NULL);
  	for(int i = 0; i < sp->count; i++)
	{
    		if(sp->data[i] == NULL)
		{
      			free(sp->data[i]);
   		}
  	}
  	free(sp->data);
  	free(sp->flag);
  	free(sp);
  	return;
}

/*
Arguments: SET *sp
Return Type: int
Functionality: Returns number of elements in the set
Big-O: O(1)
*/
int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->count;
}

/*
Arguments: SET *sp, void *elt
Return Type: void
Functionality: Inserts an element into the set
Big-O: O(1)
*/
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL && sp->count < sp->length);
  	bool find = false;
  	int index = search(sp, elt, &find);
  	if(find == false)
	{
    		sp->data[index] = elt;
    		sp->flag[index] = FILLED;
    		sp->count++;
  	} 
  	return;
}

/*
Arguments: SET *sp, void *elt
Return Type: void
Functionality: Deletes an elements from the set
Big-O: O(1)
*/
void removeElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
  	bool find = false;
  	int index = search(sp, elt, &find);
  	if(find == false)
	{
   		return;
  	}
  	sp->flag[index] = REMOVED;
  	sp->count--;
 	return;
}

/*
Arguments: SET *sp, void *elt
Return Type: void*
Functionality: search wheter a specific element is in the set
Big-O: O(1)
*/
void *findElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
  	bool find = false;
  	int index = search(sp, elt, &find);
  	if(find == false)
	{
    		return NULL;
  	}
  	return sp->data[index];
}

/*
Arguments: SET *sp
Return Type: void*
Functionality: Allocate and return an array of elements in the set pointed to by a pointer 
Big-O: O(n)
*/
void *getElements(SET *sp)
{
	assert(sp != NULL);
  	void** elts = malloc(sizeof(void*)*sp->count);
  	assert(elts != NULL);
  	int i, j;
  	for(i = 0, j = 0; i < sp->length; i++)
	{
    		if(sp->flag[i] == FILLED)
		{
      			elts[j++] = sp->data[i];
    		}
  	} 
  	quicksort(elts, 0, sp->count - 1, sp->compare);
  	return elts;
}

/*
Arguments: void **elts, int low, int high, int (*compare)()
Return Type: int
Functionality: Partitions subarray around the pivot so that the pivot is in the correct location
Big-O: O(n)
*/
static int partition(void** elts, int low, int high, int (*compare)())
{
  	void* pivot = elts[high];
  	int smaller = low - 1; 
 	for(int i = low; i <= high - 1; i++)
	{
    		if((*compare)(elts[i], pivot) <= 0) //if the element in the array is less than or equal to the pivot, swap
		{
      			smaller++; //increment index of smaller element
			void* temp = elts[smaller];
      			elts[smaller] = elts[i];
      			elts[i] = temp;
    		}
  	}
  	void* swap = elts[smaller + 1]; 
  	elts[smaller + 1] = elts[high];
  	elts[high] = swap;
  	return smaller + 1;
}

/*
Arguments: void **elts, int low, int high, int (*compare)()
Return Type: void
Functionality: Recursively sort the subarrays to the left and right of the pivot
Big-O: O(n)
*/
static void quicksort(void** elts, int low, int high, int (*compare)())
{
  	if(low < high)
	{
    		int index = partition(elts, low, high, compare);
    		quicksort(elts, low, index - 1, compare);
    		quicksort(elts, index + 1, high, compare);
  	}
  	return;
}
