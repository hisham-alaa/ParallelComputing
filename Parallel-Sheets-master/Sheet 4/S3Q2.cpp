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
	
	// 1- Broadcast
	// Data that will be shared is for example >> X
	int x;
	if(rank == 0){
		x = 10;
	}

	MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
	cout<<"[+] Broadcasting from process 0 >>> My Rank "<<rank<<", my X = "<<x<<endl;


	// 2- Gather 
	// Gather data from all Proceses into P0
	int *collector = new int[size];
	MPI_Gather(&rank, 1, MPI_INT, collector, 1, MPI_INT, 0, MPI_COMM_WORLD);
	// Don't forget this
	if(rank == 0)
		for(int i=0; i<size; i++)
			cout<<"[+] Gathering from processes into P0 >>> "<<collector[i]<<endl;

	// 3- Reduce 
	// we will make P0 to reduce in it sum, product, max, min 
	// for Processes's ranks
	int sum = 0, prod = 1, max, min;
	MPI_Reduce(&rank, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&rank, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
	MPI_Reduce(&rank, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&rank, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

	if(rank == 0){
		cout<<"[+] Total sum of ranks >>> "<<sum<<endl;
		// product must be zer0 b/c P0 it's rank = 0
		cout<<"[+] Product of ranks >>> "<<prod<<endl;
		cout<<"[+] MAX of ranks >>> "<<max<<endl;
		cout<<"[+] MIN of ranks >>> "<<min<<endl;
	}
	

	MPI_Finalize();
	return 0;
}