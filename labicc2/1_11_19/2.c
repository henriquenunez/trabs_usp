//QUICK FIND

#include <stdlib.h>
#include <stdio.h>

#define _span(a,b) b - a + 1
#define _interpol(val,min,max,size) (((val-min)/(max-min))*(size - 1))
#define _rand_interval(a,b) rand() % (_span(a,b)) + a

int get_smaller_number(int* vec, int pos, int from, int to);

/*Performs the count below in the left and right sides, for each vector position*/
int* quick_find(int* vec, int n_th, int low, int high)
{
	for (int i = low ; i <= high ; i++)
	{
		if (get_smaller_number(vec, i, low, i) +
		    get_smaller_number(vec, i, i+1, high) == n_th)
			return vec+i;
	}
}

/*Counts how many numbers are smaller than vec[pos], int the given range*/
int get_smaller_number(int* vec, int pos, int from, int to)
{
	int count = 0;
	for (int i = from ; i < to ; i++)
	{
		if (vec[i] < vec[pos]) count++;
	}

	return count;
}

/*Generates vec*/
int* genvec(int size, int a, int b)
{
	int* new_vec = (int*) malloc (size * sizeof(int));
	for (int i = 0 ; i < size ; i++)
		new_vec[i] = _rand_interval(a,b);

	return new_vec;
}

/*Prints vec*/
void printvec(int* vec, int size)
{
	int counter = 0;
	for (int i = 0 ; i < size ; i++)
	{
		printf("%d ", vec[i]);
		counter += vec[i];
	}
	printf("\n", counter);
}

int main()
{
	int *vec, size, pos;
	scanf("%d %d", &size, &pos);
	vec = genvec(size, 0, size-1);
	printvec(vec, size);
	/*Base position:offsetted position*/
	printf("%p:%p", vec, quick_find(vec, pos, 0, size-1));
}

