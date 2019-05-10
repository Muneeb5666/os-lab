#include <math.h> 
#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define size 100
int arr[size];
int half=size/2;
void mergeSort(int arr[],int l,int r);

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
void *merge1(void *arg){
mergeSort(arr,0,half);
}
void *merge2(void *arg){
mergeSort(arr,half,size);
}
void *merge3(void *arg){
mergeSort(arr,0,size);
}
void mergeSort(int arr[],int l,int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
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
    	pthread_create(&tid1,NULL,merge1,&num);
    	pthread_create(&tid2,NULL,merge2,&num);
    	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_create(&tid4,NULL,merge3,&num);
	pthread_join(tid4,NULL);
	pthread_t tid3;
	pthread_create(&tid3,NULL,printArray,&num);
	pthread_join(tid3,NULL);
    	
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0; 
} 
