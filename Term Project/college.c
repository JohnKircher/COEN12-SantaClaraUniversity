#include "data.h"

#define MAXNUMSTUDENTS 3000

int prevID = 0;

/*
Arguments: None
Return Type: int
Functionality: This is the outsider program that simulates a college admission process
to give students a unique student ID and an age. First by adding 1,000 students to the class,
giving them a unique ID and age, then finds a certain student with a unique ID and removes them from the set.
*/
int main()
{
	SET* application1;
  	srand(time(NULL));
  	application1 = createDataSet(MAXNUMSTUDENTS);
  	for(int i = 0; i < 1000; i++)
	{
    		int randomID = (rand() % 2) + 1;
    		int randomAge = (rand() % 13) + 18;
    		prevID += randomID;
    		insertion(application1, prevID, randomAge);
  	}
  	int deleteAge = (rand() % 13) + 18;
  	deletion(application1, deleteAge);
  	printf("Max Age Gap: %d\n", maxAgeGap(application1));
	destroyDataSet(application1);
}



