#include <stdio.h>
#include <sys/time.h>
#include "omp.h"

#define MAX 1000000000

int main()
{
	unsigned int i;
	double suma=0.0;
	float num=4.0;
	
	long long start_ts;
	long long stop_ts;
	int elapsed_time;
	long long lElapsedTime;
	struct timeval ts;

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial
	
	//#pragma omp parallel
	//{
		#pragma omp parallel for reduction(+:suma)
		for(i=0;i<MAX;i+=2)
		{
			suma += 4.0 / (2*i+1);
			suma -= 4.0 / (2*i+3);
			//suma = suma + num/(float) i;
			//num = num * -1.0;
			//printf("i: %d\n", i);
			//printf("num: %f\n", num);
			//printf("suma: %f\n", suma);
		}
	//}

	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (int) (stop_ts - start_ts)/1000000;
	printf("Tiempo = %d segundos\n",elapsed_time);

	printf("PI = %.20f\n",suma);
}