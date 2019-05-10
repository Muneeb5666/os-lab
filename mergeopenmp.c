#include <math.h> 
#include <stdio.h> 
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define size 100
int arr[size];

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
   
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
        
        int m = l+(r-l)/2; 
   
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 
void printArray()
{ 
	printf("after sorting = \n");
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  


int main() 
{ 
    	int i;
    	clock_t tStart = clock();
    	
	srand(time(NULL));
	for(i = 0; i < size; i++)
	{
	arr[i] = rand() % size;
	}	
	int num=size;
	printf("before sorting = \n");
	for(i = 0; i < size; i++)
	{ 
	printf("%d ", arr[i]);
	}
	printf("\n");
	int up=0,dn=0;
	#pragma omp parallel num_threads(2)
	{
	int a=omp_get_thread_num();
	int half=size/2;
	if(a==0){
	mergeSort(arr,0,half);
	up=1;
	}
	if(a==1){
	mergeSort(arr,half,size);
	dn=1;	
	}
		
	}
	mergeSort(arr,0,size);
	printArray();
	
    	
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0; 
} 
