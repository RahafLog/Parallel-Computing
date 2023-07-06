

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <iostream>


const int MAX_STRING = 100;

int main(void) {
	char greeting[MAX_STRING];
	int comm_sz;
	int my_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank != 0) {//other process not master 
		printf(greeting, "Hello, world from process with rank %d out of %d processes.\n",
			my_rank, comm_sz);

		MPI_Send(greeting, strlen(greeting) + 1 , MPI_CHAR, 0, 0, MPI_COMM_WORLD); //msg, length+1 , type , dest , sending tag, comm_world 
	}
	else {//master thread 

		printf("Hi, world from process with rank %d out of %d processes.\n", my_rank,
			comm_sz);

		for (int q = 1; q < comm_sz; q++) {

			MPI_Recv(greeting,MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //msg , length , type , src (where to send), recv tag , comm world , status 

		}
	}


	MPI_Finalize();//important in end of mpi 
	return 0;
}