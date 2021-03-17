#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
//#include "mpi.h"


int sumDivisors(int a)
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

int main(){

    int min = 1, max = 18416, rank, size;

    long long start_ts;
	long long stop_ts;
	int elapsed_time;
	long long lElapsedTime;
	struct timeval ts;

        gettimeofday(&ts, NULL);
        start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial

        //printf("ingresa el numero inferior\n");
        //scanf("%d", &min);
//
        //printf("ingresa el numero superior\n");
        //scanf("%d", &max);

    for (int a = min; a <= max; a++) {
        
        int b = sumDivisors(a);
        
        if ((a < b) && (b <= max) && (sumDivisors (b) == a)) {
            printf ("%d y %d son numeros amigos\n", a, b);
            printf ("%d y %d son numeros amigos\n", b, a);
        }
    }
            
        gettimeofday(&ts, NULL);
        stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

        elapsed_time = (int) (stop_ts - start_ts);
        printf("Tiempo = %d microsegundos\n",elapsed_time);

  return 0;
}