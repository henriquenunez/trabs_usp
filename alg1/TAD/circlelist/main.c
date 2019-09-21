#include <stdio.h>
#include "circlelist.h"

int main()
{
    LIST* aList = newList();
    insertInList(10, 200, aList);
    insertInList(5, 250, aList);
    
    printList(aList);
}
