#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define NUM 4

int arr[NUM];
int arro[NUM];

int main (argc,argv)
int argc;
char *argv[];
{
	int rank, size;
	int i;
	MPI_Init (&argc, &argv); /* starts MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &size); /* get number of processes */

	for(i=0;i<NUM;i++)
		arr[i]=(rank+1)*(i+1)+(rank+1)*(i+1)+1;
	
	printf("Proceso %d tiene %d %d %d %d\n",rank,arr[0],arr[1],arr[2],arr[3]);
	
	MPI_Reduce(arr,arro,NUM,MPI_INT,MPI_SUM,2,MPI_COMM_WORLD);

	sleep(1);
	printf("Proceso %d tiene %d %d %d %d\n",rank,arro[0],arro[1],arro[2],arro[3]);


	MPI_Finalize();
	return 0;
}