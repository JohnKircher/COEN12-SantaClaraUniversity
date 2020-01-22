#include "data.h"

#define MAXSTUDENTS 3000

int prevID = 0;//used to keep track of previous student's ID

/*
Arguments: None
Return Type: int
Functionality: This is the outsider program that simulates a college admission process
to give students a unique student ID and an age. First by adding 1,000 students to the class, 
giving them a unique ID and age, then finds a certain student with a unique ID and removes them from the set.
*/
int main()
{
	SET* application2;
  	srand(time(NULL)); //random number generator
  	application2 = createDataSet(MAXSTUDENTS);
  	int studentNumber = 0;
  	puts("Adding Students:");
  	while(studentNumber < 1000)
	{
    		int randomID = (rand() % 2) + 1;
    		int randomAge = (rand() % 13) + 18;
    		prevID += randomID;
    		insertion(application2, prevID, randomAge);
    		studentNumber++; // looks at the next student
  	}  
  	int deleteID = (rand() % 2000) + 1;
  	deletion(application2, deleteID); //delete the student if found in the list
  	destroyDataSet(application2); //destroy the data set
}
