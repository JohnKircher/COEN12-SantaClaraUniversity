//Include Libraries and "set.h" and define EMPTY, DELETED, FILLED
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#define EMPTY 0
#define DELETED 1
#define FILLED 2

//Defining the strcuture set
struct set
{
	int count;
	int length;
	char **data;
	int *flags;
	int (*compare)();
	unsigned (*hash)();
};

/*
Arguments: SET *sp, char *elt, bool *found, int *delete
Return Type: int
Functionality: Uses Linear Probing to search through the table and find position. Checks 3 cases, FILLED, DELETED, EMPTY.  
*/
// average O(1), worst case O(n)
static int search(SET *sp, void * elt, bool * found, int *delete)
{
	assert(sp != NULL && elt != NULL);
	int position;
	*found = false;
	bool deleted = false;
	for(int i = 0; i < sp->length; i++)
	{
		position = ((*sp->hash)(elt) + i) % sp->length;

		if(sp->flags[position] == EMPTY)
		{
			*found = false;
			return position;
		}
		else if(sp->flags[position] == FILLED)
		{
			if((*sp->compare)(sp->data[position], elt) == 0)
			{
			 	*found = true;
				return position;
			}
		}
		else if(sp->flags[position] == DELETED)
		{
			if(deleted == false)
			{
				deleted = true;
				*delete = position;
			}			
			return position;
		}
	}	
	return -1;

}

/*
Arguments: int maxElts, int(*compare)(), unsigned(*hash)()
Return Type: SET *
Functionality: Creates and allocates memory for the set, initializes as empty
and returns a pointer to the set
*/
// O(n)
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)())
{
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->data = malloc(sizeof(char *)*maxElts);
	assert(sp->data != NULL);
	sp->flags = malloc(sizeof(char *)*maxElts);
	assert(sp->flags != NULL);
	for(int i = 0; i < maxElts; i++)
	{
		sp->flags[i] = EMPTY;
	}
	sp->compare = compare;
	sp->hash = hash;
	return sp;
}

/*
Arguments: SET *sp
void destroySet(SET *sp)rguments: SET *sp
Return Type: void
Functionality: If table is filler, free's the memory of the elements, then the array, then the table, then the pointer
*/
// O(1)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	free(sp->data);
	free(sp);
	free(sp->flags);
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
Arguments: SET *sp, void *elt
Return Type: void
Functionality: Add's elements to the array, makes sure they are not duplicates or the array is not full
*/
// average  O(1) worst case O(n)
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
	if(sp->count == sp->length)
	{
		return;
	}

	int index;
	bool found;
	int y = -1;
	index = search(sp, elt, &found, &y);
	if(found)
	{
		return;
	}	
	else
	{
		if(y >= 0)
		{
			sp->data[y] = elt;
			sp->flags[y] = FILLED;
		}
		else if(y < 0)
		{
			sp->data[index] = elt;
			sp->flags[index] = FILLED;
		}
		(sp->count)++;
	}	
}

/*
Arguments: SET *sp, void *elt
Return Type: void
Functionality: Removes elemnets from the array
*/
// average O(1) worst case O(n)
void removeElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
	bool found;
	int y = -1;
	int index = search(sp, elt, &found, &y);
	if(found == false)
	{
		return;
	}
	else
	{
		sp->flags[index] = DELETED;
		(sp->count)--;
	}
}

/*
Arguments: SET *sp, void *elt
Return Type: void *
Functionality: Finds the element returned from the search function
*/
// average O(1) worst case O(n)
void *findElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
	int index;
	bool found;
	int y = -1;
	index = search(sp, elt, &found, &y);
	if(!found)
	{
		return NULL;
	}
	else
	{
		return sp->data[index];
	}
}

/*
Arguments: SET *sp
Return Type: void *
Functionality: Gets and returns the elements from the data
*/
//O(n)
void *getElements(SET *sp)
{
	int i;
	int j;
	assert(sp != NULL);
	void **elements;
	elements = malloc(sizeof(void *) *sp->count);
	assert(elements != NULL);
	for(i = 0, j =0; i < sp->length; i++)
	{	
		if(sp->flags[i] == FILLED)
		{
			elements[j++] = sp->data[i];
		}
	}
	return elements;
}




