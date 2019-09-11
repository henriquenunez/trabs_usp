#include <stdio.h>
#include <stdlib.h>

typedef struct _node NODE;

struct _node {	
	int content;
	NODE* next;
};

NODE* newNode(int data);
float getAverage(NODE* head);
//void insertAtNode(NODE* node, int data);
void printList(NODE* list);
void push(NODE** head, NODE* node);
//float insertSmaller(NODE** head, int value);
//void push(NODE** head, NODE* node);
//NODE* searchSmaller(NODE** head, int value);

int main(){
	int num, input;
	NODE* head = NULL;

	scanf("%d", &num);

	for (int i = 0; i < num; i++)
	{	
		scanf("%d", &input);
		push(&head, newNode(input));
	}

	printList(head);

	printf("%f\n", getAverage(head));
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

float getAverage(NODE* head){
	NODE* temp = head;
	float average;
	int count = 0;
//	while(temp->next != NULL)
	while(1){
		average = count*(average)+(temp->content);
		count++;
		average /= count;
		if(temp -> next == NULL)
			break;
		temp = temp->next;
	}
	
	return average;
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
