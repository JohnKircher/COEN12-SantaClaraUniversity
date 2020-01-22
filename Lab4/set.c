// Include Libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "set.h"
#include "list.h"
#define CHAIN 20

//Create Strcuture set
struct set
{
	LIST** data;
  	int length;
  	int count;
  	int (*compare)();
  	unsigned (*hash)();
};

/*
Arguments: int maxElts, int (*compare)(), unsigned (*hash(()
Return Type: SET
Functionality: Creates a linked list in each slot of the hash table for the ADT
*/
// Big-O Runtime O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
  	SET *sp = (SET*)malloc(sizeof(SET));
  	assert(sp != NULL);
  	sp->count = 0;
  	sp->length = (maxElts/CHAIN); 
  	sp->compare = compare;
  	sp->hash = hash;
  	sp->data = malloc(sizeof(LIST*)*sp->length);
  	assert(sp->data != NULL);
  	for(int i = 0; i < sp->length; i++)
  	{
    		sp->data[i] = createList(sp->compare);
  	}
  	return sp;
}

/*
Arguments: SET *sp
Return Type: void
Functionality: destroys the set
*/
// Big-O Runtime: O(n)
void destroySet(SET *sp)
{
  	assert(sp != NULL);
  	for(int i = 0; i < sp->length; i++)
  	{
  		destroyList(sp->data[i]);
  	}
  	free(sp->data);
  	free(sp);
  	return;
}

/*
Arguments: SET *sp
Return Type: int
Functionality: returns number of elements currently in the set
*/
// Big-O Runtime: O(1)
int numElements(SET *sp)
{
  	assert(sp != NULL);
  	return sp->count;
}

/*
Arguments: SET *sp, void *elt
Return Type: void
Functionality: insert an element into the set
*/
// Big-O Runtime O(1)
void addElement(SET *sp, void *elt)
{
  	assert(sp != NULL && elt != NULL);
	int index = (*sp->hash)(elt) % sp->length;
	if(findItem(sp->data[index], elt) != NULL)
	{
		return;
	} 
  	addFirst(sp->data[index], elt);
  	sp->count++; 
  	return;
}

/*
Arguments: SET *sp, void *elt
Return Type: void
Functionality: removes an element from the set
*/
// Big-O Runtime O(1)
void removeElement(SET *sp, void *elt)
{
  	assert(sp != NULL && elt != NULL);
	int index = (*sp->hash)(elt) % sp->length; 
  	removeItem(sp->data[index], elt);
  	sp->count--;
  	return;
}

/*
Arguments: SET *sp, void *elt
Return Type: void *
Functionality: returns a specific element in the set
*/
// Big-O Runtime O(1)
void *findElement(SET *sp, void *elt)
{
  	assert(sp != NULL && elt != NULL);
	int index = (*sp->hash)(elt) % sp->length; 	
  	return findItem(sp->data[index], elt);
}

/*
Arguments: SET *sp
Return Type: void *
Functionality: allocate and return an array of elements in the set pointed to by a pointer
*/
// Big-O Runtime O(n)
void *getElements(SET *sp)
{
	int i;
	int j;
  	assert(sp != NULL);
  	void** elts = malloc(sizeof(void*)*sp->count);
  	assert(elts != NULL);
  	for(i = 0, j = 0; i < sp->length; i++)
  	{
  		void** copyList = getItems(sp->data[i]);
  		memcpy(elts + j, copyList, sizeof(void*)*numItems(sp->data[i])); 
      		j+= numItems(sp->data[i]); 
		free(copyList);
    		
 	} 
 	return elts;
}


