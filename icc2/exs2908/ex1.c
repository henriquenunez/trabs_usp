#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numWrong(char* beReviewed){
	int len = strlen(beReviewed);
	int count = 0;
	int i = 0;

	for (i = 0; i < (len-1); i++){
		printf("%d %d\t", beReviewed[i+1], beReviewed[i]+1);
		if(beReviewed[i+1] < beReviewed[i]){
			/*printf("sla\n");*/
			++count;
		}else{
			/*printf("asla\n");*/
		}
	}
	return count;
}

int main(){
	char input[30];
	int numComp;
	/*unsigned long int len;*/
	/*getline(&input, &len, stdin);*/
	scanf("%s", input);
	printf("%s\n", input);

	numComp = numWrong(input);

	if(numComp == 2 || numComp == 0){
		printf("There are the chance\n");
	}else{
		printf("There aren't the chance\n");
	}
	return 0;
}