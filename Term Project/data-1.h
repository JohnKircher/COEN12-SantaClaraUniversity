#ifndef DATA_H
#define DATA_H

#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node NODE;
typedef struct set SET;

SET* createDataSet(int maxStudents);
void destroyDataSet(SET* sp);
int searchID(SET* sp, int matchID);
void insertion(SET* sp, int insertID, int insertAge);
void deletion(SET* sp, int deleteID);

#endif
