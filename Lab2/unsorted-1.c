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
Arguments: SET *sp, char *elt
Return Type: int
Functionality: Loops through all the elements and returns the element if it is found, 
if not it returns -1 
*/
// O(n)
static int search(SET *sp, char * elt)
{
	assert(sp != NULL & elt != NULL);
	for(int i = 0; i < sp->count; i++)
	{
		if(strcmp((sp->data[i]), elt) == 0)
		{
			return i;
		}
	}
	return -1;
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
	if(search(sp, elt) != -1)
	{
		return;
	}
	else
	{
		elt = strdup(elt);
		assert(elt != NULL);
		sp->data[sp->count] = elt;
		(sp->count)++;
	}
	
}

/*
Arguments: SET *sp, char *elt
Return Type: void
Functionality: Removes elemnets from the array and shifts the elements down
*/
// O(n)
void removeElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	if(search(sp, elt) == -1)
	{
		return;	
	}
	else
	{
		int a = search(sp, elt);
		free(sp->data[a]);
		(sp->data[a]) = (sp->data[(sp->count) - 1]);
		(sp->count)--;
	}
}

/*
Arguments: SET *sp, char *elt
Return Type: char *
Functionality: Finds the element returned from the search function
*/
// O(n)
char *findElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	if(search(sp, elt) == -1)
	{
		return NULL;
	}
	return sp->data[search(sp, elt)];

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




