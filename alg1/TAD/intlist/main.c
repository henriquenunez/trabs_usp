#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "intlist.h"

//#define LIST_MAX_NUM 100

int main(){
    int nEle;
    int temp;
    LIST a_list;

    scanf("%d", &nEle);

    a_list = newList();//new list

    for (int i = 0; i < nEle; i++){
	        scanf("%d", &temp);
	        //printf("got: %d\n", temp);
	        if(retLen(a_list) < 100){
	        	if(!whetherInList(a_list, temp)) //checks if the list has the right size and the element is already in
	               insElement(a_list, temp);
	        }else{
	            printf("Lista cheia. Impossível realizar o processamento.\n");
	            return 0;
	        }
    	}
    printList(a_list);
    printf("Tamanho da lista: %d\n", retLen(a_list));
    printf("Total de comparações: %d\n", compNum(a_list));

    return 0;
}