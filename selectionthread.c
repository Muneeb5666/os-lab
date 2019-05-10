#include <math.h> 
#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define size 100
int arr[size];
int half=size/2;


void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
void *selectionSortup(void *arg) 
{ 
    int i, j, min_idx; 
  
    for (i = 0; i < half-1; i++) 
    { 
       
        min_idx = i; 
        for (j = i+1; j < half; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
         
        swap(&arr[min_idx], &arr[i]); 
    } 
} 

void *selectionSortdn(void *arg) 
{ 
    int i, j, min_idx; 
  
    
    for (i = half; i < size-1; i++) 
    { 
     
        min_idx = i; 
        for (j = half; j < size; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  

        swap(&arr[min_idx], &arr[i]); 
    } 
} 

void *selectionSort(void * arg) 
{ 
    int i, j, min_idx; 
  
     
    for (i = 0; i < size-1; i++) 
    { 
  
        min_idx = i; 
        for (j = i+1; j < size; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
   
        swap(&arr[min_idx], &arr[i]); 
    } 
}  

void *printArray(void *arg) 
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
	pthread_t tid1,tid2,tid4;
    	pthread_create(&tid1,NULL,selectionSortup,&num);
    	pthread_create(&tid2,NULL,selectionSortdn,&num);
    	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_create(&tid4,NULL,selectionSort,&num);
	pthread_join(tid4,NULL);
	pthread_t tid3;
	pthread_create(&tid3,NULL,printArray,&num);
	pthread_join(tid3,NULL);
    	
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0; 
} 
