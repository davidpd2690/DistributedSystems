#include <stdio.h>


int main() 
{ 
	int arr[] = {10, 7, 8, 9, 1, 5}; 
	int n = sizeof(arr)/sizeof(arr[0]); 
    printf("n: %d\n", n);
	//quickSort(arr, 0, n-1); 
	printf("Sorted array: n"); 
	//printArray(arr, n); 
	return 0; 
} 