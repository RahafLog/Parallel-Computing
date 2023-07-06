#include <iostream>
#include <omp.h>

int Vector_Sum(int x[], int n);

int main(int argc, char* argv[]) {

    int thread_count = 100;
    const int n = 1000;
    int x[n];

    for (int i = 0; i < n; i++) {
        x[i] = 1;
    }

    int sum = 0;

    printf("within %d threads and vector of size %d each element of value 1 \n", thread_count, n);

                                                  
#pragma omp parallel for num_threads(thread_count) reduction(+: sum) 

    //Activity 4 using OMP parallel for 
    for (int i = 0; i < n; i++) {
        sum += x[i];
    }

    //{ Activity 5 using Crtitical 
      //  int my_sum = Vector_Sum(x, n);
    //  #pragma omp critical
        //sum += my_sum; }


    printf("sum= %d", sum); //print the sum
    printf("\n");

    return 0;
}
 
int Vector_Sum(int x[], int n) {

    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    int local_n = n / thread_count;
    int my_first = my_rank * local_n;
    int my_last = my_first + local_n;

    int my_sum = 0;

    for (int i = my_first; i < my_last; i++) {
        my_sum += x[i];
    }

    return my_sum;
}