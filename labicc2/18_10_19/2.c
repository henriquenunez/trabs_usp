#include <stdio.h>
#include <stdlib.h>

/*
typedef enum apple_sizes
{
	ONE,
	TWO,
	THREE,
	FOUR
} aapl_size;


typedef enum apple_colors
{
	RED,
	GREEN,
	YELLOW,
	BLUE
} aapl_colour;
*/

typedef struct _i_need_iphone
{
	int color;
	int   size;
} AAPL;


void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

int partition_color(AAPL* arr, int low, int high) 
{ 
    int pivot = arr[high].color;    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j].color < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i].color, &arr[j].color); 
        } 
    } 
    swap(&arr[i + 1].color, &arr[high].color); 
    return (i + 1); 
} 
  
void quickSort_color(AAPL* arr, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition_color(arr, low, high); 
        quickSort_color(arr, low, pi - 1); 
        quickSort_color(arr, pi + 1, high); 
    } 
} 

int partition_size(AAPL* arr, int low, int high) 
{ 
    int pivot = arr[high].size;    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high - 1; j++)
    { 
        // If current element is smaller than the pivot 
        if (arr[j].size < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i].size, &arr[j].size); 
        } 
    } 
    swap(&arr[i + 1].size, &arr[high].size); 
    return (i + 1); 
} 
  
void quickSort_size(AAPL* arr, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition_size(arr, low, high); 
        quickSort_size(arr, low, pi - 1); 
        quickSort_size(arr, pi + 1, high); 
    } 
}

AAPL generateApples(AAPL* emptyApples, int n)
{
    for(int i = 0; i < n; i++)
    {
        emptyApples[i].color = rand() % 4; 
        emptyApples[i].size  = rand() % 4;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    AAPL* my_apples = (AAPL*) malloc(sizeof(AAPL) * n);
    AAPL amounts = generateApples(my_apples, n);
    printf("");

	return 0;
}

