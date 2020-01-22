//include libraries
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

//Algorithms to determine the parent, left, and right children for a given node
static int parent(int i);
static int left(int i);
static int right(int i);

static int parent(int i)
{
	return (i-1)/2;
}

static int left(int i)
{
	return (i*2) + 1;	
}

static int right(int i)
{
	return (i*2) + 2;
}

//Create struct pqueue
struct pqueue
{
	int count; //number of entries in the array
	int length; //length of allocated array
	void **data; //allocated array of entries
	int (*compare)(); //compare function
};

/*
Arguments: int (*compare)()
Return Type: PQ
Functionality: Creates a queue and sets the starting array size to 10 
*/
// Big-O Runtime: O(1)
PQ *createQueue(int (*compare)())
{
	PQ *pq = malloc(sizeof(PQ));
	assert(pq != NULL);
	pq->compare = compare;
	pq->count = 0;
	pq->length = 10;
	pq->data = malloc(sizeof(void*)*10);
	assert(pq->data != NULL);
	return pq;
}

/*
Arguments: PQ *pq
Return Type: void
Functionality: Destroys the priority queue
*/
// Big-O Runtime: O(n)
void destroyQueue(PQ *pq)
{
	assert(pq != NULL);
	for(int i = 0; i < pq->count; i++)
	{
		free(pq->data[i]);
	}
	free(pq->data);
	free(pq);
	return;
}

/*
Arguments: PQ *pq
Return Type: int
Functionality: returns the number of integers currently in the priority queue
*/
// Big-O Runtime: O(1)
int numEntries(PQ *pq)
{
	assert(pq != NULL);
	return pq->count;
}

/*
Arguments: PQ *pq, void *entry
Return Type: void
Functionality: inserts into the priority queue
*/
// Big-O Runtime: O(logn)
void addEntry(PQ *pq, void *entry)
{
	assert(pq != NULL);
	if(pq->count == pq->length)
	{
		pq->length *= 2;
		pq->data = realloc(pq->data, sizeof(void*)*pq->length);
	}
	pq->data[pq->count] = entry;
	int newIndex = pq->count;
	while(pq->count != 0 && (*pq->compare)(pq->data[parent(newIndex)], pq->data[newIndex]) > 0)
	{
		void* swapData = pq->data[newIndex];
		pq->data[newIndex] = pq->data[parent(newIndex)];
		pq->data[parent(newIndex)] = swapData;
		newIndex = parent(newIndex);
	}
	pq->count++;
	return;
}

/*
Arguments: PQ *pq
Return Type: void
Functionality: removes from the priority queue
*/
// Big-O Runtime: O(logn)
void *removeEntry(PQ *pq)
{
	assert(pq != NULL);
	void* removeData = pq->data[0];
	pq->data[0] = pq->data[pq->count - 1];
	int index = 0;
	while(left(index) <= pq->count - 1)
	{
		int smallerChildIndex = left(index);
		if(right(index) <= pq->count - 1)
		{
			if((*pq->compare)(pq->data[right(index)], pq->data[left(index)]) < 0)
			{
				smallerChildIndex = right(index);
			}
		}
		if((*pq->compare)(pq->data[index], pq->data[smallerChildIndex]) < 0)
		{
			break;
		}
		else
		{
			void* swapData = pq->data[index];
			pq->data[index] = pq->data[smallerChildIndex];
			pq->data[smallerChildIndex] = swapData;
		}
		index = smallerChildIndex;
	}
	pq->count--;
	return removeData;	
}
