
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(void) {
	long n, i;
	int thread_count;
	double factor;
	double sum = 0.0;

	thread_count = 8;
	n = 10000;

	double stime, ftime, exec_time;
	stime = omp_get_wtick();
	
#  pragma omp parallel for num_threads(thread_count) \
      reduction(+: sum) private(factor) 

	for (i = 0; i < n; i++) {
		factor = (i % 2 == 0) ? 1.0 : -1.0;
		sum += factor / ((2.0 * i) + 1.0); 
	}

	sum = 4.0 * sum;

	ftime = omp_get_wtime();
	exec_time = ftime- stime;

	printf("With n = %d terms and %d threads,\n", n, thread_count);
	printf("   Our estimate of pi = %.14f\n", sum);

	//printf("sum = %d", sum);
	printf("\n\nTime taken is ====> %f\n", exec_time);


	return 0;
}  /* main */