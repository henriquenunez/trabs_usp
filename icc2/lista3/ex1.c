//Every possile combination of N first letters

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int check_ok(int* vec, int n)
{
	for (int i = 1; i <= n; i++)
		if (vec[i] == 0) return false;
	return true;
}

void printVec(int* vec, int n)
{
	for (int i = 1; i <= n; i++)
	{
		printf("%c ", 64+vec[i]);
	}
	printf("\n");
}

void fillRec(int* essevec, int n)
{
//	printVec(essevec, n);

	if (check_ok(essevec, n))
	{
		//printf("tamo aizz\n");
		printVec(essevec, n);

		return;
	}

	for(int i = 1; i <= n; i++)
	{
		if(essevec[i] == 0)
		{
			int* newvec = (int*) malloc (sizeof(int) * n+1);
//			copyvecs(newvec, essevec, n);
			memcpy(newvec, essevec, sizeof(int)*n+1);
			newvec[i] = ++newvec[0];
			fillRec(newvec, n);
			free(newvec);
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);

	int* basevec = (int*) calloc (n+1, (n+1)*sizeof(int));
	fillRec(basevec, n);

	free();
	return 0;
}
