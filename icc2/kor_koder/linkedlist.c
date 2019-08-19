#include <stdio.h>
#include <stdlib.h>

typedef struct _list_element listElement;

struct _list_element{
	int content;
	listElement* next;
};

listElement* insertAtNode(listElement** prev; int data){

	listElement* new_node;
	new_node = (listElement*) malloc(sizeof(listElement));
	new_node->content = data;
	
	if( (*prev)->next != NULL){
		new_node->next = (*prev)->next;
	}else{
		new_node->next = NULL;
	}
	
	(*prev)->next = new_node;
	
	return new_node;
}

listElement* searchLesserNode(listElement* beginning, int data){
	listElement* temp;

	if (beginning->next=NULL){
		return beginning;
	}

	temp->next = beginning->next;

	do{
		if (data < temp->next->content){
			return temp->next;
		}
		temp->next = temp->next->next;

	}while(tmp->next != NULL);

	return NULL;
}

void printList(listElement* beginning){
	listElement* temp = beginning;
	while(temp->next != NULL){
		printf("%d\n", temp->content);
		temp = temp->next;
	}
}

int main(){
	int input;
	listElement* begin, temp;

	while(scanf("%d", &input) && input != -1){
		temp = insertAtNode(temp, input);
	}

	printList(begin);
	
}