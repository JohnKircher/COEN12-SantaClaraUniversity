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
};


static unsigned strhash(char *s)
{
	unsigned hash = 0;
	while(*s != '\0')
	{
		hash = 31 * hash + *s++;
	}
	return hash;
}


/*
Arguments: SET *sp, char *elt, bool *found
Return Type: int
Functionality: Uses Linear Probing to search through the table and find position. Checks 3 cases, FILLED, DELETED, EMPTY.  
*/
// average O(1), worst case O(m)
static int search(SET *sp, char * elt, bool * found)
{
	assert(sp != NULL);
	int position;
	int placeholder = -1;
	unsigned key;
	*found = false;
	key = strhash(elt);
	for(int i = 0; i < sp->length; i++)
	{
		position = (key + i) % (sp->length);

		if(sp->flags[position] == FILLED)
		{
			if(strcmp(elt, sp->data[position]) == 0)
			{
				*found = true;
				return position;
			}
		}
		if(sp->flags[position] == DELETED)
		{
			if(placeholder == -1)
			{
			 	placeholder = position;
			}
		}
		if(sp->flags[position] == EMPTY)
		{
			if(placeholder != -1)
			{
				return placeholder;
			}			
			return position;
		}
	}	
	return placeholder;

}

/*
Arguments: int maxElts 
Return Type: SET *
Functionality: Creates and allocates memory for the set, initializes as empty
and returns a pointer to the set
*/
// O(n)
SET *createSet(int maxElts)
{
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->data = malloc(sizeof(char *)*maxElts);
	assert(sp->data != NULL);
	sp->flags = malloc(sizeof(int *)*maxElts);
	assert(sp->flags != NULL);
	for(int i = 0; i < maxElts; i++)
	{
		sp->flags[i] = EMPTY;
	}
	return sp;
}

/*
Arguments: SET *sp
void destroySet(SET *sp)rguments: SET *sp
Return Type: void
Functionality: If table is filler, free's the memory of the elements, then the array, then the table, then the pointer
*/
// O(n)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	for(int i = 0; i < sp->length; i++)
	{
		if(sp->flags[i] == FILLED)
		{
			free(sp->data[i]);
		}
	}
	free(sp->data);
	free(sp->flags);
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
// average  O(1) worst case O(n)
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
	if(found)
	{
		return;
	}	
	if(index == -1)
	{
		return;
	}
	sp->data[index] = strdup(elt);
	(sp->count)++;
	sp->flags[index] = FILLED;	
}

/*
Arguments: SET *sp, char *elt
Return Type: void
Functionality: Removes elemnets from the array
*/
// average O(1) worst case O(n)
void removeElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	bool found;
	int index = search(sp, elt, &found);
	if(found == false)
	{
		return;
	}
	free(sp->data[index]);
	sp->flags[index] = DELETED;
	(sp->count)--;
}

/*
Arguments: SET *sp, char *elt
Return Type: char *
Functionality: Finds the element returned from the search function
*/
// average O(1) worst case O(n)
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
	return sp->data[index];
}

/*
Arguments: SET *sp
Return Type: char **
Functionality: Gets and returns the elements from the data
*/
// average O(1) worst case O(n)
char **getElements(SET *sp)
{
	int i;
	int j;
	assert(sp != NULL);
	char ** elements;
	elements = malloc(sizeof(char *) *sp->count);
	assert(elements != NULL);
	for(i = 0, j =0; i < sp->length; i++)
	{
		
		if(sp->flags[i] == FILLED)
		{
			elements[j] = sp->data[i];
			j++;
		}
	}
	return elements;
}




