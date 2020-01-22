//Include Libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

//create node struct with next, prev, and void *data
typedef struct node
{
	void *data;
	struct node *next;
	struct node *prev;
}NODE;

//create list struct with count, NODE *head, and compare
typedef struct list
{
	int count;
	NODE *head;
	int (*compare)();
}LIST;

/*
Arguments: int (*compare)()
Return Type: LIST
Functionality: allocates memory for the dummy node and the head, set the head pointers to themselves
*/
// Big-O Runtime: O(1)
LIST *createList(int (*compare)())
{
	LIST *pList = malloc(sizeof(LIST));
	assert(pList != NULL);
	pList->count = 0;
	pList->head = malloc(sizeof(NODE));
	assert(pList->head != NULL);
	pList->compare = compare;
	pList->head->prev = pList->head;
	pList->head->next = pList->head;
	return pList;	
}

/*
Arguments: LIST *lp
Return Type: void
Functionality: free's all the nodes from the List
*/
// Big-O Runtime: O(n) 
void destroyList(LIST *lp)
{
	assert(lp != NULL);
	NODE *pDel = lp->head->prev;
	NODE *pPrev;
	while(pDel != lp->head)
	{
		pPrev = pDel->prev;
		free(pDel);
		pDel = pPrev;
	}
	free(pDel);
	free(lp);
}

/*
Arguments: LIST *lp
Return Type: int
Functionality: returns the amount of items in the list
*/
// Big-O Runtime: O(1)
int numItems(LIST *lp)
{
	assert(lp != NULL);
	return lp->count;
}

/*
Arguments: LIST *lp, void *item
Return Type: void
Functionality: Adds an item to the beginning of the list
*/
// Big-O Runtime O(1)
void addFirst(LIST *lp, void *item)
{
	assert(lp != NULL);
	NODE *addNode = malloc(sizeof(NODE));
	assert(addNode != NULL);
	addNode->data = item;
	lp->head->next->prev = addNode;
	addNode->next = lp->head->next;
	addNode->prev = lp->head;
	lp->head->next = addNode;
	lp->count++;
	return;
}

/*
Arguments: LIST *lp, void *item
Return Type: void
Functionality: Adds an item to the end of the list
*/
// Big-O Runtime O(1)
void addLast(LIST *lp, void *item)
{
	assert(lp != NULL);
	NODE *addNode = malloc(sizeof(NODE));
	assert(addNode != NULL);
	addNode->data = item;
	lp->head->prev->next = addNode;
	addNode->next = lp->head;
	addNode->prev = lp->head->prev;
	lp->head->prev = addNode;
	lp->count++;
	return;
}

/*
Arguments: LIST *lp
Return Type: void *
Functionality: Removes an item from the beginning of the list
*/
// Big-O Runtime O(1)
void *removeFirst(LIST *lp)
{
	assert(lp != NULL && lp->count > 0);
	NODE *itemToDelete = lp->head->next;
	void *copy = itemToDelete->data;
	lp->head->next = itemToDelete->next;
	itemToDelete->next->prev = lp->head;
	free(itemToDelete);
	lp->count--;
	return copy;
}

/*
Arguments: LIST *lp
Return Type: void *
Functionality: Removes an item from the end of the list
*/
// Big-O Runtime O(1)
void *removeLast(LIST *lp)
{
	assert(lp != NULL && lp->count > 0);
        NODE *itemToDelete = lp->head->prev;
        void *copy = itemToDelete->data;
        lp->head->prev = itemToDelete->prev;
        itemToDelete->prev->next = lp->head;
        free(itemToDelete);
        lp->count--;
        return copy;
}

/*
Arguments: LIST *lp
Return Type: void *
Functionality: returns the data of the first node
*/
// Big-O Runtime O(1)
void *getFirst(LIST *lp)
{
	assert(lp != NULL && lp->count > 0);
	return lp->head->next->data;
}

/*
Arguments: LIST *lp
Return Type: void *
Functionality: returns the data of the last node
*/
// Big-O Runtime O(1)
void *getLast(LIST *lp)
{
	assert(lp != NULL && lp->count > 0);
	return lp->head->prev->data;
}

/*
Arguments: LIST *lp, void *item
Return Type: void
Functionality: Traverses through the list, if an item match is found, it removes, otherwise it keeps traversing 
*/
// Big-O Runtime O(n)
void removeItem(LIST *lp, void *item)
{
	assert(lp != NULL);
	if(lp->count > 0)
	{
		NODE *flag = lp->head->next;
		while(flag != lp->head)
		{
			if((*lp->compare)(flag->data, item) == 0)
			{
				flag->prev->next = flag->next;
				flag->next->prev = flag->prev;
				free(flag);
				lp->count--;
				break;
			}
			else
			{
				flag = flag->next;
			}
		}
	}
	return;
}

/*
Arguments: LIST *lp, void *item
Return Type: void *
Functionality: Find's an item in the list if it is a match, otherwse, keep traversing
*/
// Big-O Runtime O(n)
void *findItem(LIST *lp, void *item)
{
	assert(lp != NULL);
	if(lp->count > 0)
	{
		NODE *flag = lp->head->next;
		while(flag != lp->head)
		{
			if((*lp->compare)(flag->data, item) == 0)
			{
				return flag->data;
			}
			else
			{
				flag = flag->next;
			}
		}
	}
	return NULL;
}

/*
Arguments: LIST *lp
Return Type: void *
Functionality: traverse through the linked list and copy data to the temporary array
*/
// Big-O Runtime O(n)
void *getItems(LIST *lp)
{
	assert(lp != NULL);
	void **temp = malloc(sizeof(void*)*lp->count);
	assert(temp != NULL);
	int x = 0;
	NODE *flag = lp->head->next;
	while(flag != lp->head)
	{
		temp[x++] = flag->data;
		flag = flag->next;
	}
	return temp;
}
