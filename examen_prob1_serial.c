#include <stdio.h> 
#include <sys/time.h>


#define N 10000

int A[N];

int main(){

    long long start_ts;
	long long stop_ts;
	int elapsed_time;
	long long lElapsedTime;
	struct timeval ts;

    int i;
    int s = 1;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial

    for(i=0;i<N;i++)
    {
        s = s + i*2 - 1;
        A[i] = s;
    }

    for(i=0;i<N;i++)
    {
        printf("%d\n", A[i]); 
    }

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (int) (stop_ts - start_ts);
	printf("Tiempo = %d microsegundos\n",elapsed_time);

}

