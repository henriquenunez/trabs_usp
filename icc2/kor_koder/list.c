#include <stdio.h>
#include <stdlib.h>

typedef struct _node NODE;

struct _node {	
	int content;
	NODE* next;
};

NODE* newNode(int data);
NODE* searchSmaller(NODE* head, int value);
void insertAtNode(NODE* node, int data);
void printList(NODE* list);
void push(NODE** head, NODE* node);
void insertSmaller(NODE** head, int value);
//void push(NODE** head, NODE* node);
//NODE* searchSmaller(NODE** head, int value);

int main(){
	int num, input;
	NODE* head = NULL;

	scanf("%d", &num);
//	fprintf(stderr, "%d", num);
	for (int i = 0; i < num; i++)
	{	
		scanf("%d", &input);
		//fprintf(stderr, "%d", input);		
		insertSmaller(&head, input);
	}

	printList(head);
}

NODE* newNode(int data){
	NODE* new = (NODE*) malloc(sizeof(NODE));
	new->content = data;
	
	if(new != NULL)
		return new;
	else
		return NULL;
}

void push(NODE** head, NODE* node){
	node->next = (*head);
	(*head) = node;
}

void insertAtNode(NODE* node, int data){
	NODE* new = newNode(data);
	
	if(node->next != NULL)
		new->next = node->next;
	node->next = new;
	
	return;
}

void insertSmaller(NODE** head, int value){
	//NODE* temp = (*head);
	
	if(*head == NULL){
		//printf("head was null\n");
		*head = newNode(value);
		return;
	}

	if((*head)->content >= value){
		//printf("head was greater\n");
		push(head, newNode(value));
		return;
	}
/*	
	if((*head)->content < value){
		insertAtNode(*head, value);
		return;
	}
*/
	insertAtNode(searchSmaller((*head), value), value);
}


NODE* searchSmaller(NODE* head, int value){
	NODE* temp = head;
	
//	while(temp->next != NULL)
	while(1){
		if (temp->next != NULL){
			if(temp->content < value && temp->next->content > value){
				//printf("less than val");
				return temp;
			}
			temp = temp->next;	
		}else{
			if(temp->content < value){
				return temp;
			}
		}
	}
	
	return NULL;
}

void printList(NODE* head){
	NODE* temp;
	temp = head;

	while(temp != NULL){
		printf("%d", temp->content);
		temp = temp->next;
		if(temp == NULL){
			printf("\n");
		}else{
			printf(" ");
		}
	}
}
