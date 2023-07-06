

#include <iostream>
#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(void) { 
    int comm_sz;                                   
    int my_rank;
    int sum=0;
                                                     
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    double local_start, local_fininsh, local_elapsod, elpsed; 

    //to make all process work togther 
    MPI_Barrier(MPI_COMM_WORLD);

    local_start = MPI_Wtime(); // to calculate 

    //to sum up the process rank of all the processes. The final  result is in process 0
    MPI_Reduce(&my_rank, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 

    if(my_rank == 0 )
    printf("Sum rank of %d processes, is %d \n", comm_sz, sum);

    //to send the result of the summation from process 0 to all other processes.
    MPI_Bcast(&sum, 1, MPI_INT, 0, MPI_COMM_WORLD); 
    printf("After Bcast processe %d : sum rank of %d process is %d \n ", my_rank, comm_sz, sum);

    local_fininsh = MPI_Wtime(); 
    local_elapsod = local_fininsh - local_start;
    MPI_Reduce(&local_elapsod, &elpsed, 1, MPI_DOUBLE, MPI_MAX , 0, MPI_COMM_WORLD); // to calculate the time of work all process and the result in 0

    if (my_rank == 0)
    printf("Max elpsode time %d of %f processes \n", comm_sz, elpsed); //send the result to process 0 

    MPI_Finalize(); 
    return 0; 

}
