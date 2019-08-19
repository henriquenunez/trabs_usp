#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "intlist.h"

int main(){
    int nEle;
    int temp;
    integerList* a_list;

    scanf("%d", &nEle);

    a_list = newList();

    for (int i = 0; i < nEle; i++){
        scanf("%d", &temp);
        if(!whetherInList(a_list, temp)){
            insElement(a_list, temp);
        }
    }

    printList(a_list);
    printf("Tamanho da lista: %d\n", retLen(a_list));
    printf("Total de comparações: %d\n", compNum(a_list));

    return 0;
}