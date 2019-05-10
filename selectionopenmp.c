#include <math.h> 
#include <stdio.h> 
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define size 100
int arr[size];

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void selectionSort(int a,int s) 
{ 
    int i, j, min_idx; 
  
    for (i = a; i < s-1; i++) 
    { 
        min_idx = i; 
        for (j = i+1; j < size; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        swap(&arr[min_idx], &arr[i]); 
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
	selectionSort(0,half);
	up=1;
	}
	if(a==1){
	selectionSort(half,size);
	dn=1;	
	}
		
	}
	selectionSort(0,size);
	
	printArray();
    	
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0; 
} 
