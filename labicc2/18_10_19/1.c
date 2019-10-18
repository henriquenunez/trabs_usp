#include <stdio.h>
#include <stdlib.h>

#define A 65

void genWands(int* wand_storage, int num)
{		
	for(int i = 0; i < num ; i++)
	{
		wand_storage[i] = A + (rand() % 4);
		printf("%c ", wand_storage[i]);
	}
	printf("\n");
}


void printWands(int* wand_storage, int num)
{		
	for(int i = 0; i < num ; i++)
	{
		//wand_storage[i] = A + (rand() % 4);
		printf("%c ", wand_storage[i]);
	}
	printf("\n");
}


void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 


int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

void quickSort(int arr[], int low, int high) 
{ 
    int pi = partition();
    if (low < high) 
    { 
  	
        quickSort(arr, pi + 1, high); 
    } 
} 
  
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 


void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 


int main()
{
	int n;
	printf("Insert number of wands\n");
	scanf("%d", &n);
	int* wands = (int*) malloc (sizeof(int) * n);
	genWands(wands, n);
	mergeSort(wands, 0, n-1);
	printWands(wands, n);

	return 255;
}
