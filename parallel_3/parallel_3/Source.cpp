/*#include<iostream>
#include<mpi.h>

using namespace std;
int main() {
	MPI_Init(NULL, NULL);
	
	MPI_Status s;
	int id = 0,size=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	/*
	char machineName[MPI_MAX_PROCESSOR_NAME];
	int len=0;
	MPI_Get_processor_name(machineName, &len);

	cout << "hello world form "<<id <<" out of "<<size <<" its name is " <<machineName<< endl;

	int x = 100, y = rand()%100;
	
	if (id != 0)
		cout << "Value in process " << id << " is " << y << endl;

	MPI_Allreduce(&y, &x,1,MPI_INT,MPI_SUM, MPI_COMM_WORLD);
	
	cout << x << " is the summation " << endl;



	MPI_Finalize();
	return 0;
}
*/

#include<iostream>
using namespace std;
int main (){

	int x, y;
	cout << "enter two values to sum ";
	cin >> x >>y;

	cout <<"the summation of your values is "<<x+y;


	return 0;
}


/*
#include<iostream>
#include<mpi.h>
using namespace std;

#define SIZE 1000000
int main() {
	// Parallel Region
	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	if (size != 2) {
		if (rank == 0)
			cout << "[-] ERROR, Number of processors...";
		MPI_Finalize();
		exit(1);
	}

	int* V1=new int[SIZE], * V2=new int[SIZE];
	if (rank == 0)
		for (int i = 0; i < SIZE; i++)
			V1[i] = V2[i] = rand();
	
	MPI_Barrier(MPI_COMM_WORLD);
	double start = MPI_Wtime();

	int len = SIZE / 2;
	int localSum = 0;
	int globalSum = 0;

	int* myArr1, * myArr2;
	myArr1 = new int[len];
	myArr2 = new int[len];

	MPI_Scatter(V1, SIZE, MPI_INT, myArr1, len, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(V2, SIZE, MPI_INT, myArr2, len, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < len; i++)
		localSum += myArr1[i] * myArr2[i];

	MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	double end = MPI_Wtime();

	if (rank == 0) {
		cout << "sum = " << globalSum << endl;
		cout << "time is = " << end - start << endl;
	}

	MPI_Finalize();
	return 0;
}
*/



/*
#include<iostream>
#include<mpi.h>
#include<omp.h>
#include<pthread.h>

using namespace std;

double resPI = 0;

pthread_t pithread[100];
pthread_mutex_t mute;

void* calc(void* arg) {
	double id = (int)arg;
	double temppi=0;
	temppi = 4.0 / (100 * (1 + ((float)(id*id) /(100*100))));
	pthread_mutex_lock(&mute);
	resPI += temppi;
	pthread_mutex_unlock(&mute);
	return NULL;
}

void pthreadPI() {
	pthread_mutex_init(&mute,NULL);

	for (int i = 0; i < 100; i++)
		pthread_create(&pithread[i], NULL, *calc, (void*)i);
	
	for (int i = 0; i < 100; i++)
		pthread_join(pithread[i], NULL);

	pthread_mutex_destroy(&mute);
}

void ompPI() {
	#pragma omp parallel for reduction(+:resPI)
	for (double i = 0; i < 100; i++)
		resPI += 4.0 / (100 * (1 + ((float)(i * i) / (100 * 100))));
}


int main() {

	
	ompPI();

	cout << " PI value is " << resPI << endl;


	/*
	MPI_Init(NULL, NULL);

	MPI_Status s;
	int id = 0,n=0, size = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	int* x,*y,*copyx,*copyy ;
	
	if (size != 0)
	{
		cout << "Number of processes have to be 2 "<< endl;
		MPI_Finalize();
		exit(1);
	}
	if (id == 0) {
		cout << " Enter array size " << endl;
		cin >> n;
		x= new int[n];
		y = new int[n];
		copyx = new int[n / 2];
		copyy = new int[n / 2];

		for (int i = 0; i < n; i++)
		{
			x[i] = y[i] = rand() % 100;
		}

		for (int i = 0; i < n / 2; i++)
		{
			copyx[i] = x[n-i-1];
			copyy[i] = y[n-i-1];
		}
		MPI_Send(copyx,);
	}
	MPI_Allreduce(&y, &x, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	cout << x << " is the summation " << endl;



	MPI_Finalize();
	

	return 0;
}
*/