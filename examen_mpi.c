#include <stdio.h> 
#include <sys/time.h>
#include <mpi.h>


#define N 10000

int A[N];

int main(int argc, char ** argv){

    long long start_ts;
	long long stop_ts;
	int elapsed_time;
	long long lElapsedTime;
	struct timeval ts;

    int i, rank, size;
    int s = 1;

    MPI_Init (&argc, &argv); /* starts MPI */
    MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */
    MPI_Comm_size (MPI_COMM_WORLD, &size); /* get number of processes */

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial

    MPI_Bcast(A, N, MPI_INT, 0, MPI_COMM_WORLD);
    for(i=0;i<N;i++)
    {
        //s = s + i*2 - 1;
        A[i] = i*i; 
    }

    for(i=0;i<N;i++)
        printf("%d\n", A[i]);
    

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (int) (stop_ts - start_ts);
	printf("Tiempo = %d microsegundos\n",elapsed_time);

    MPI_Finalize();

}

