#include<iostream>
#include<math.h>
#include<vector>
#include<omp.h>
using namespace std;
// *compilation line*
// g++ [FILE_NAME].cpp -fopenmp -o out.exe
// *run command*
// out.exe

int N = 1000;

struct Matrix {
	int **M;
	Matrix() {
		M = new int*[N];
		for(int i = 0; i < N; i++)
			M[i] = new int[N];
	}

	void fill(int tk){
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				M[i][j] = tk;
	}

	int* operator[](int indx)
	{
		return M[indx];
	}

	void disp()
	{
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++)
				cout << M[i][j] << " ";
			cout << endl;
		}
		cout << endl << endl;
	}

}A,B,C;


int main()
{	

	A.fill(1);
	B.fill(2);

	if(N <= 10)
	{
		A.disp();
		B.disp();
	}

	C.fill(0);

	double wt1 = omp_get_wtime();
	#pragma omp parallel
	{	
		#pragma omp for
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
				for(int k = 0; k < N; k++)
				{
					C[i][j] += A[i][k]*B[k][j];
				}
		}
	}
	double wt2 = omp_get_wtime();
	cout << "Time = " << wt2-wt1 << endl;

	if(N <= 10)
		C.disp();
	return 0;
}