//libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

//global variables & declarations & intitilaize functions
#define MAX_WORD_LENGTH 30
void readFile(char *file);

/*
Arguments: int argc, char *argv[]
Return Type: int 
Fucntionality: Checks to make sure there are not too many inputs or file names is not missing.
Then calls the function readFile(char *file)
*/
int main(int argc, char *argv[1])
{
	if(argc == 1)
	{
		printf("the file name is missing\n");
		return 0;
	}
	else if(argc > 2)
	{
		printf("Too many inputs\n");
		return 0;
	}
	readFile(argv[1]);
}

/*
Arguments: char *file
Return Type: void
Functionality: This function reads all the words from a text file.
*/
void readFile(char *file)
{
	FILE *fp;
	int count = 0;
	char ch[MAX_WORD_LENGTH];
	if((fp = fopen(file, "r")) == NULL)
	{
		printf("Cannot open file\n");
		return;
	}
	while(fscanf(fp, "%s", ch) == 1)
	{
		count++;	
	}
	printf("%d total words\n", count);
	fclose(fp);
	return;
}

