#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "omp.h"

#define MAX 30000000

int esprimo(int n);

int main()
{
	int i;
	int primos=0;
	float num=4.0;
	
	long long start_ts;
	long long stop_ts;
	int elapsed_time;
	long long lElapsedTime;
	struct timeval ts;

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial
	
    #pragma omp parallel for
	    for(i=1;i<MAX;i++)
        {
            if(esprimo(i))
	    		primos++;
        }
	    	
	
    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (int) (stop_ts - start_ts)/1000000;
	printf("Tiempo = %d segundos\n",elapsed_time);

	printf("Primos encontrados = %d\n",primos);
}

int esprimo(int n)
{
	int d=3;
	int fueprimo=1;
	int limite;
	
	limite=sqrt(n);
	
	if(n==1)
		fueprimo=0;
	else if(n==2)
		fueprimo=1;
	else if(n%2==0)	// Es par
		fueprimo=0;
	else
	{
		while(n%d && d<=limite)
			d+=2;
		fueprimo=d>limite;
	}
	return(fueprimo);
}