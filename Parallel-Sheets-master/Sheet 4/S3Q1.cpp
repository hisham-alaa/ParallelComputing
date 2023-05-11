#include<iostream>
#include<mpi.h>
using namespace std;

#define SIZE 1000000
int main(){
	// Parallel Region
	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	// Check number of Processors must be 2
	if(size != 2){
		if(rank == 0)
			cout<<"[-] ERROR, Number of processors...";
		MPI_Finalize();
		exit(1);
	}

	// Vectors as input
	// make P0 owner of them and initialize them
	int *V1, *V2;
	if(rank == 0){
		V1 = new int[SIZE];
		V2 = new int[SIZE];
		for(int i=0; i<SIZE; i++)
			V1[i] = V2[i] = 1;
	}
	// Start Parallel Region, to compute Time we need
	// All thread start together
	MPI_Barrier(MPI_COMM_WORLD);
	double start = MPI_Wtime();

	// Distribute two vectors over 2 processors
	// P0 will distribut this work becose he is owner of 2 Vectors
	// will use temp to fill it and send to P1
	// will fill it w/ sec part of each Vector
	int *temp;
	int len = SIZE/2;
	int localSum = 0;
	int globalSum = 0;
	if(rank == 0){
		temp = new int[len];
		
		// Sec half of First Vector
		for(int i=0; i<len; i++)
			temp[i] = V1[len + i];
		MPI_Send(temp, len, MPI_INT, 1, 10, MPI_COMM_WORLD);
		
		// Sec half of Sec Vector
		for(int i=0; i<len; i++)
			temp[i] = V2[len + i];
		MPI_Send(temp, len, MPI_INT, 1, 11, MPI_COMM_WORLD);

		//Now P0 will apply dot product
		// on first part for each vector
		for(int i=0; i<len; i++)
			localSum += V1[i] * V2[i] ;
	}


	//Now P1 recive his part, in myArr1 and myArr2 
	// and apply dot product
	int *myArr1, *myArr2;
	if(rank == 1){
		myArr1 = new int[len];
		myArr2 = new int[len];
		MPI_Recv(myArr1, len, MPI_INT, 0, 10, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(myArr2, len, MPI_INT, 0, 11, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		for(int i=0; i<len; i++)
			localSum += myArr1[i] * myArr2[i] ;
	}

	// Now we need to reduce local sum of each Pi
	// in global sum
	MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	// End of Parallel Region
	MPI_Barrier(MPI_COMM_WORLD);
	double end = MPI_Wtime();

	if (rank == 0){
		cout << "sum = " << globalSum << endl;
		cout << "time is = " << end - start << endl;
	}

	MPI_Finalize();
	return 0;
}