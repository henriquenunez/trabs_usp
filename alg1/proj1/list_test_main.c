#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main()
{
	LIST* ourList = newList();
	
	printList(ourList);

	insertFirst(ourList, newNode(3));
	insertAtNode(ourList, searchByKey(ourList, 3) , newNode(2));
	insertAtNode(ourList, searchByKey(ourList, 3) , newNode(5));
	insertAtNode(ourList, searchByKey(ourList, 3) , newNode(7));
	insertAtNode(ourList, searchByKey(ourList, 3) , newNode(69));
	insertAtNode(ourList, searchByKey(ourList, 3) , newNode(666));
	insertAtNode(ourList, searchByKey(ourList, 3) , newNode(1));
	insertAtNode(ourList, searchByKey(ourList, 3) , newNode(0));

	removeByKey(ourList, 666);
	removeByKey(ourList, 69);

	printList(ourList);

	deAlloc(ourList);

	return 0;
}