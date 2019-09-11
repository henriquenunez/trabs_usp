#ifndef INTEGER_LIST
#define INTEGER_LIST

typedef struct _list integerList;

typedef integerList* LIST; //pointer to list datatype

LIST newList(); //create list
void insElement(LIST list, int d); //insert element
int whetherInList(LIST list, int num); //checks if exists in list
void printList(LIST list); //prints list
int retLen(LIST list); //acquires length
int compNum(LIST list); //acquires number of comparisons
int getNum(LIST list, int pos); //acquires the element itself

#endif