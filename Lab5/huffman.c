//include libraries
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "pqueue.h"
#include "pack.h"
#include <ctype.h>


typedef struct node NODE;

static void readFile(char *fileName);
static NODE* mkNode(int data, NODE* left, NODE* right);
static int depth(NODE* np);
static int nodeCmp(NODE* np1, NODE* np2);

int counts[257];
NODE* nodes[257];

/*
Arguments: int argc, char* argv[]
Return Type: int
Functionality: reads the file, creates the priority queue, and prints out the bits from the characters in the text file 
*/
// Big-O Runtime: O(n)
int main(int argc, char* argv[])
{
	if(argc !=  3)
	{
		printf("%s\n", "error");
		return 0;
	}
	else
	{
		readFile(argv[1]);
	}
	
	PQ *pq = createQueue(nodeCmp);
	for(int i = 0; i < 256; i++)
	{
		if(counts[i] > 0)
		{
			nodes[i] = mkNode(counts[i], NULL, NULL);
			addEntry(pq, nodes[i]);
		}
	}

	nodes[256] = mkNode(0, NULL, NULL);
	addEntry(pq, nodes[256]);

	while(numEntries(pq) > 1)
	{
		NODE* left = removeEntry(pq);
		NODE* right = removeEntry(pq);
		addEntry(pq, mkNode(left->count + right->count, left, right));
	}
	for(int i = 0; i <= 256; i++)
	{
		if(nodes[i] != NULL)
		{
			if(isprint(i))
			{
				printf(" '%c' ", i);
			}
			else
			{
				printf("%03o", i);
			}
			printf(": %d x %d bits = %d bits\n", counts[i], depth(nodes[i]), counts[i]*depth(nodes[i]));	//print out the bits used for each character in the text file
		}	
	}
	pack(argv[1], argv[2], nodes);
	destroyQueue(pq);
	return 0;
}

/*
Arguments: char* fileName
Return Type: void
Functionality: reads the text file 
*/
// Big-O Runtime: O(n)
static void readFile(char* fileName)
{
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		printf("%s\n", "File name missing");
		return;
	}
	int c;
	while((c = getc(fp)) != EOF)
	{
		counts[c]++;		
	}
	fclose(fp);
	return;
}

/*
Arguments: int data, NODE* left, NODE* right 
Return Type: NODE*
Functionality: makes a node for the priority queue 
*/
// Big-O Runtime: O(1)
static NODE* mkNode(int data, NODE* left, NODE* right)
{
	NODE* np = malloc(sizeof(NODE));
	assert(np != NULL);
	np->count = data;
	np->parent = NULL;
	if(left != NULL)
	{
		left->parent = np;
	}
	if(right != NULL)
	{
		right->parent = np;
	}
	return np;	
}

/*
Arguments: NODE* np
Return Type: int
Functionality: returns the depth
*/
// Big-O Runtime: O(1)
static int depth(NODE* np)
{
	assert(np != NULL);
	if(np->parent == NULL)
	{
		return 0;		
	}
	return depth(np->parent) + 1; 		
}

/*
Arguments: NODE* np1, NODE* np2
Return Type: int
Functionality: Compares both node pointers 
*/
// Big-O Runtime: O(1)
static int nodeCmp(NODE* np1, NODE* np2)
{
	assert(np1 != NULL && np2 != NULL);
	return (np1->count < np2->count) ? -1 : (np1->count > np2->count);  
} 

