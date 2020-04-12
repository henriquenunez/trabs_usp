#include <stdio.h>
#include <stdlib.h>

typedef struct _towers{
	int* towA;
	int* towR;
	int* towE;
} TOWERS;

TOWERS* createTowers(int n){
	TOWERS* newSet = (TOWERS*) malloc (sizeof(TOWERS));
	newSet->towA = (int *) calloc (n, sizeof(int)*n);
	newSet->towR = (int *) calloc (n, sizeof(int)*n);
	newSet->towE = (int *) calloc (n, sizeof(int)*n);
}

void populateTowers(int n, TOWERS* aSet){
	for(int i = 0; i < n; i++)
		aSet->towA[i] = n-i;
	}

void clear(int n, TOWERS* aSet){
	for(int i = 0; i < n; i++){
		fprintf(stdout, "\033[F");
	}
}

int printTowers(int n, TOWERS* aSet){
	for(int i = 0; i < n; i++){
		fprintf(stdout, "%d\t%d\t%d\n", aSet->towA[i], aSet->towR[i], aSet->towE[i]);
	}
}

void printTowersWithoutADT(int n, int* towA, int* towR, int* towE){
	for(int i = 0; i < n; i++){
		fprintf(stdout, "%d\t%d\t%d\n", towA[i], towR[i], towE[i]);
	}
}

void moveDisks(int n, int* from, int* to, int* using, int (*printTowers)(int ndele, TOWERS* aSet)){
	if (n == 1){
		to[0] = from[0];
		from[0] = 0;
	}
	if(n > 1){
		moveDisks(n-1, from, using, to);
		to[n-1] = from[n-1];
		from[n-1] = 0;
		moveDisks(n-1, using, to, from);
	}
	(*printTowers)(ndele, aSet);
}

int main(){
	int n;
	scanf("%d", &n);
	TOWERS* thisSet = createTowers(n);
	populateTowers(n, thisSet);
	printTowers(n, thisSet);
	moveDisks(n, thisSet->towA, thisSet->towE, thisSet->towR);
	printTowers(n, thisSet);

	return 0;
}
