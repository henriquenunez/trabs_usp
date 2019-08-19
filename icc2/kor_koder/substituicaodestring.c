#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int StrSearch(char* baseString, char* schString){
	int index;
	int i;
	int j;
	bool keepSearching = true;
	bool found = false;

	for (i = 0; i < strlen(baseString); i++){
		
		if (i + strlen(schString) > strlen(baseString)){
			keepSearching = false;
		}
		
		if(!keepSearching) break;

		for (j = 0; j < strlen(schString); j++){
			//printf("comparing %c with %c\n", baseString[i+j], schString[j]);
			if (baseString[i+j] != schString[j]){
				//printf("wrong at %d\n", j);
				j = 0;
				break;
			}
		}
		//printf("j: %d strlen: %d\n", j, strlen(schString));
		if (j == strlen(schString)){
			//printf("foundue!\n");
			index = i;
			found = true;
			break;
		}
	}
	if (found != true) index = -1;

	return index;
}

void pullVals(char* baseString, unsigned int len){
	unsigned int probablyFalseNum = strlen(baseString);
	int i;
	char* buffer = (char*) malloc(len*sizeof(char));
	int procedureBegin = -1;

	for (i = probablyFalseNum; i < len; i++){
		if (baseString[i] != 0){
			procedureBegin = i;
			break;
		}
	}
	if (procedureBegin != -1){
		memcpy(buffer, baseString+procedureBegin, len - procedureBegin);
		memset(baseString+probablyFalseNum, 0, len - probablyFalseNum);
		memcpy(baseString+probablyFalseNum, buffer, strlen(buffer));
	}
}

void StrReplace(char* baseString, unsigned int index, unsigned int schLen, char* replString){
	int saveLen = strlen(baseString);
	if (strcmp("\"\"", replString) == 0){
		
		memset(replString, 0, strlen(replString));
	}
	memset(baseString+index, 0, schLen);
	memcpy(baseString+index, replString, strlen(replString));
	pullVals(baseString, saveLen);
}

int main (){
	
	char* input = NULL;
	char* baseString;
	char* schString;
	char* replString;
	unsigned long int len;
	getline(&input, &len, stdin);
	
	baseString = (char*) malloc(len*sizeof(char));
	schString = (char*) malloc(len*sizeof(char));
	replString = (char*) malloc(len*sizeof(char));

	sscanf(input, "%s %s %s", baseString, schString, replString);

	//printf("can replace at: %d\n", );
	StrReplace(baseString, StrSearch(baseString, schString), strlen(schString), replString);
	printf("%s\n", baseString);
}