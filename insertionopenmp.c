#include <math.h> 
#include <stdio.h> 
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define size 100
int arr[size];


void insertionSort(int a,int s) 
{ 
    int i, key, j; 
    for (i=a; i < s; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
        
        while (j >= a && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
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
	insertionSort(0,half);
	up=1;
	}
	if(a==1){
	insertionSort(half,size);
	dn=1;	
	}
		
	}
	insertionSort(0,size);
	
	printArray();
	
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    	
  
    return 0; 
} 
