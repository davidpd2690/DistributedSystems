#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>


int sum(int a)
{
    int s = 0;

    for(int i = 1; i <= a/2; i++)
    {
        if(a % i == 0)
        {
            s += i;
        }
    }

    return s;
}

int main(int argc, char ** argv)
{

    long long start_ts;
	long long stop_ts;
	int elapsed_time;
	long long lElapsedTime;
	struct timeval ts;
    
    int min, max, rank, size;
    //int range[2];

    MPI_Init (&argc, &argv); /* starts MPI */
    MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */
    MPI_Comm_size (MPI_COMM_WORLD, &size); /* get number of processes */
   
    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial

    if(rank == 0)
    {
        printf("ingresa el valor minimo\n");
        scanf("%d", &min);
        //range[0] = min;
        printf("ingresa el valor maximo\n");
        scanf("%d", &max);
        //range[1] = max;

        printf("proceso: %d - min antes de bcast: %d\n", rank, min);
        printf("proceso: %d - max antes de bcast: %d\n", rank, max);
    }

    MPI_Bcast(&min, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&max, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("proceso: %d - min despues de bcast: %d\n", rank, min);
    printf("proceso: %d - max despues de bcast: %d\n", rank, max);

    for (int a = min; a <= max; a++) 
    {
        
        int b = sum(a);
        int g;
            
            if ((a < b) && (b <= max) && (sum(b) == a)) 
            {
                printf ("%d y %d son numeros amigos\n", a, b);
                printf ("%d y %d son numeros amigos\n", b, a);
                
            }
    }
    
            
        gettimeofday(&ts, NULL);
        stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

        elapsed_time = (int) (stop_ts - start_ts);
        printf("Tiempo = %d microsegundos\n",elapsed_time);

    MPI_Finalize();

  return 0;
}