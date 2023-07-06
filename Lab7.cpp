#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <iostream>

/*
matrix-vector multiplication
*/

void Mat_vect_mult(int local_A[], int x[], int local_y[], int local_m, int n, MPI_Comm comm /*in*/); 

int main(void) {

	int my_rank, comm_sz, 
		m = 8/*number of rows*/, 
		n = 4 /*number of columns*/,
		local_m;

	int A[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 }; // m*n 8*4=32

	int x[4] = { 0, 1, 3, 4 }; // n
	int y[8]; // m

	int local_A[32]; // local_m * n
	int local_y[8]; // local_m

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	local_m = m / comm_sz; //( rows * number of process )

	printf("Proccess %d\n", my_rank);


	MPI_Scatter(A , local_m * n , MPI_INT, local_A, local_m * n, MPI_INT, 0, MPI_COMM_WORLD);

	// DEfine variables local_start, local_finish, local_elapsed, elapsed
	double local_start, local_fininsh, local_elapsod, elpsed;
	//invoking MPI_Barrier
	MPI_Barrier(MPI_COMM_WORLD);
	//invoking MPI_Wtime();
	local_start = MPI_Wtime();


	Mat_vect_mult(local_A, x , local_y, local_m, n, MPI_COMM_WORLD);


	//invoking MPI_Wtime();
	//calculating local_elapsed
	//invoking MPI_Reduce
	local_fininsh = MPI_Wtime();
	local_elapsod = local_fininsh - local_start;
	MPI_Reduce(&local_elapsod, &elpsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	if (my_rank == 0)
		printf("Max elpsode time %d of %f processes \n", comm_sz, elpsed);
	printf("Proc %d > Elapsed time = %f seconds\n", my_rank, local_elapsod);

	//put all the elemts into one array
	MPI_Gather(local_y, local_m, MPI_INT, y, local_m, MPI_INT, 0, MPI_COMM_WORLD);

	if (my_rank == 0) {
		printf("A:\n");
		for (int i = 0; i < m * n; i++) {
			printf("%d:%d\n", i, A[i]);
		}

		printf("X:\n");
		for (int i = 0; i < n; i++) {
			printf("%d:%d\n", i, x[i]);
		}

		printf("A*X:\n");
		for (int i = 0; i < m; i++)
			printf("%d: %d\n", i, y[i]);
	}

	MPI_Finalize();
	return 0;
}

// An MPI matrix-vector multiplication function
void Mat_vect_mult(int local_A[], int x[], int local_y[], int local_m, int n, MPI_Comm comm) {

	int local_i, j;

	MPI_Bcast(x, n, MPI_INT, 0, comm);

	for (local_i = 0; local_i < local_m; local_i++) {
		local_y[local_i] = 0;
		for (j = 0; j < n; j++)
			local_y[local_i] += local_A[local_i * n + j] * x[j];
	}
}

