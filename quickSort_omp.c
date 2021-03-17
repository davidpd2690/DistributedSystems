#include <stdio.h> 
#include <sys/time.h>
#include "omp.h"

// para intercambiar la posicion de elementos del arreglo
void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
/* toma el ultimo elemento como pivote y lo coloca
en el lugar correcto dentro del arreglo ordenado. 
los elementos menor al pivote quedan de lado izquierdo del pivote
y los mayores al pivote quedan de lado derecho del pivote */
int partition (int arr[], int low, int high) 
{ 
	int pivot = arr[high]; // pivote 
	int i = (low - 1); // indice del elemento mas pequeño Index of smaller element 

	for (int j = low; j <= high-1; j++) 
	{ 
		// If current element is smaller than the pivot
        //si el elemento actual es menor al pivote 
		if (arr[j] < pivot) 
		{ 
			i++; //incrementa el indice del elemento mas pequeño increment index of smaller element 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 


//low: indice de inicio Starting index, 
//high: indice de final Ending index 
void quickSort(int arr[], int low, int high) 
{ 
	if (low < high) 
	{ 
		/* pi is partitioning index, arr[p] is now 
		at right place */
        //indice de particion, el pivote esta en el lugar correcto
		int ip = partition(arr, low, high); 

        #pragma omp task shared(arr) firstprivate(low,ip)
		{quickSort(arr, low, ip - 1);}  //izquierda
         
        #pragma omp task shared(arr) firstprivate(high,ip)
		{quickSort(arr, ip + 1, high);} //derecha

        #pragma omp taskwait
	} 
} 

// para imprimir el arreglo
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
} 


int main() 
{ 

    long long start_ts;
	long long stop_ts;
	int elapsed_time;
	long long lElapsedTime;
	struct timeval ts;

    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial

	int arr[] = {10, 7, 8, 9, 1, 5, 50, 20, 4, 3, 56, 78, 89, 
                1, 2, 4, 66, 87, 98, 100, 234, 756, 93, 9274, 9,
                123, 43,547,4567,86,345,85687,234,6,45,2346,4,
                78,124,456,14,235,13,15,12, 13,462,457547,454,23,
                2361,626,76547,75,23,7457,14,62,6347,135,2846}; 
	
    int n = sizeof(arr)/sizeof(arr[0]);     //sizeof arr / 4
	
    printf("arreglo desordenado: \n");
    printArray(arr, n);
    printf(" \n");

    quickSort(arr, 0, n-1);     //se ordena el arreglo
	
    printf("arreglo ordenado: \n"); 
	printArray(arr, n);
    printf(" \n");

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (int) (stop_ts - start_ts);
	printf("Tiempo = %d microsegundos\n",elapsed_time);

	return 0; 
} 
