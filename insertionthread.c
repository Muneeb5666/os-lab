#include <math.h> 
#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define size 100
int arr[size];
int half=size/2;

void *insertionSortup(void *arg) 
{ 
    	int i, key, j; 
    	for (i = 1; i < half; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
      
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
}
void *insertionSortdn(void *arg) 
{ 
    	int i, key, j; 
    	for (i = half; i < size; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
      
        while (j >= half && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
}
void *insertionSort(void *arg) 
{ 
    	int i, key, j; 
    	for (i = 0; i < size; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
      
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
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
    	pthread_create(&tid1,NULL,insertionSortup,&num);
    	pthread_create(&tid2,NULL,insertionSortdn,&num);
    	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_create(&tid4,NULL,insertionSort,&num);
	pthread_join(tid4,NULL);
	pthread_t tid3;
	pthread_create(&tid3,NULL,printArray,&num);
	pthread_join(tid3,NULL);
	
	
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0; 
} 
