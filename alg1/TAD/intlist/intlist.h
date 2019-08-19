#ifndef INTEGER_LIST
#define INTEGER_LIST

typedef struct _list integerList;

typedef integerList* integerList8;

integerList8 newList();
void insElement(integerList8 list, int d);
int whetherInList(integerList8 list, int num);
void printList(integerList8 list);
int retLen(integerList8 list);
int compNum(integerList8 list);
int dat_num(integerList8 list, int pos);

#endif