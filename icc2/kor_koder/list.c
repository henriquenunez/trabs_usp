#include <stdio.h>
#include <stdlib.h>

typedef struct _node NODE;

struct _node {	
	int content;
	NODE* next;
};

NODE* newNode(int data);
void insertAtSmaller(NODE** head, int data);
void printList(NODE* list);
//NODE* searchSmaller(NODE* list, int value);

int main(){
	int num, input;
	NODE* head;
	NODE* temp;

	scanf("%d", &num);
	for (int i = 0; i < num; i++)
	{	
		scanf("%d", &input);
		insertAtSmaller(&head, input);
	}
	printList(head);
}

void insertAtSmaller(NODE** head, int data){
	NODE* new;
	NODE* current;
	NODE* previous;
	new = (NODE*) malloc(sizeof(NODE));

	new->content = data;

	if (*head == NULL){
		*head = new;
		return;
	}

	current = *head;
	previous = current;

	while(current != NULL){
		if(current->content > data){
			new->next = current;
			previous->next = new;
		}
	}
	
}

void printList(NODE* head){
	NODE* temp;
	temp = head;
	while(temp != NULL){
		printf("content: %d\n", temp->content);
		temp = temp->next;
	}
}

