//Include Libraries and "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

//Defining the strcuture set
struct set
{
	int count;
	int length;
	char **data;
};

/*
Arguments: SET *sp, char *elt, bool *found
Return Type: int
Functionality: Loops through the elements and returns mid or low, otherwise low and high are shifted if
element is lower than the value or higher  
*/
// O(logn)
static int search(SET *sp, char * elt, bool * found)
{
	assert(sp != NULL & elt != NULL);
	int low = 0;
	int high = (sp->count) - 1;
	int mid;
		
	while(low <= high)
	{
		mid = (high + low)/2;
		if(strcmp((sp->data[mid]), elt) == 0)
		{
			*found = true;
			return mid;
		}
		else if(strcmp((sp->data[mid]), elt) < 0)
		{
			low = mid + 1;	
		}
		else
		{
			high = mid - 1;
		}
	}
	*found = false;
	return low;
}

/*
Arguments: int maxElts 
Return Type: SET *
Functionality: Creates and allocates memory for the set, initializes as empty
and returns a pointer to the set
*/
// O(1)
SET *createSet(int maxElts)
{
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->data = malloc(sizeof(char *)*maxElts);
	assert(sp->data != NULL);
	return sp;
}

/*
Arguments: SET *sp
void destroySet(SET *sp)rguments: SET *sp
Return Type: void
Functionality: Free's the memory of the elements, then the array, then the pointer to the set
*/
// O(n)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	for(int i = 0; i < sp->count; i++)
	{
		free(sp->data[i]);	
	}
	free(sp->data);
	free(sp);
}

/*
Arguments: SET *sp
Return Type: int
Functionality: Returns the count
*/
// O(1)
int numElements(SET *sp)
{
	assert(sp != NULL);
	return(sp->count);
}

/*
Arguments: SET *sp, char *elt
Return Type: void
Functionality: Add's elements to the array, makes sure they are not duplicates or the array is not full
*/
// O(n)
void addElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	if(sp->count == sp->length)
	{
		return;
	}

	int index;
	bool found;
	index = search(sp, elt, &found);
	
	if(!found)
	{
		for(int i = sp->count; i > index; i--)
		{
			sp->data[i] = sp->data[i-1];
		}
		sp->data[index] = strdup(elt);
		(sp->count)++;
	}
	
}

/*
Arguments: SET *sp, char *elt
Return Type: void
Functionality: Removes elemnets from the array and shifts the elements
*/
// O(n)
void removeElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	bool found;
	int index = search(sp, elt, &found);
	if(found)
	{
		free(sp->data[index]);
		for(int i = index; i < sp->count -1; i++)
		{
			sp->data[i] = sp->data[i+1];
		}
		(sp->count)--;
	}
}

/*
Arguments: SET *sp, char *elt
Return Type: char *
Functionality: Finds the element returned from the search function
*/
// O(logn)
char *findElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	int index;
	bool found;
	index = search(sp, elt, &found);
	if(!found)
	{
		return NULL;
	}
	return sp->data[search(sp, elt, &found)];
}

/*
Arguments: SET *sp
Return Type: char **
Functionality: Copies the memmory of the data to a new array
*/
// O(1)
char **getElements(SET *sp)
{
	assert(sp != NULL);
	char ** elements;
	elements = malloc(sizeof(char *) *sp->count);
	assert(elements != NULL);
	return memcpy(elements, sp->data, sizeof(char *)* sp->count);	
}




