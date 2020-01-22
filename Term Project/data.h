#ifndef DATA_H
#define DATA_H

#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct student STUDENT;
typedef struct list LIST;
typedef struct set SET;

SET* createDataSet(int maxStudents);
void destroyDataSet(SET* sp);
int searchAge(SET* sp, int matchAge);
void insertion(SET* sp, int insertID, int insertAge);
void deletion(SET* sp, int deleteAge);
int maxAgeGap(SET* sp);
void destroyDataSet(SET* sp);

#endif
