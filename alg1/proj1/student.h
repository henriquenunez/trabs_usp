#ifndef _STUDENT_H_
#define _STUDENT_H_

typedef struct _student STUDENT;
typedef struct _classroom CLASSROOM;

CLASSROOM* newTable();
void dropTable(CLASSROOM*);
void printTable(CLASSROOM*);
void printApprovedTable(CLASSROOM*);
float acquireAverage(CLASSROOM*);

int createEntry(CLASSROOM*, int, float, float, float);
int deleteEntryByKey(int);
void printEntryValueByKey(int);

int deleteEntry(void*, int);

#endif