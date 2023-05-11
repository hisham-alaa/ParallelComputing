#include<iostream>
#include<omp.h>
using namespace std;

// *compilation line*
// g++ [FILE_NAME].cpp -fopenmp -o out.exe
// *run command*
// out.exe

long N = 100000; // 9 0's
int main()
{
	int*arr = new int[N];
	for(int i = 0; i < N; i++)
		arr[i] = 1;
	long sum = 0;
	double wt1 = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp single
		{
			#pragma omp taskloop reduction(+:sum)
			for(long i = 0; i < N; i++)
				sum += arr[i];
		}
	}
	double wt2 = omp_get_wtime();
	cout << "sum = " << sum << endl;
	cout << "Time (in seconds) = " << wt2 - wt1 << endl;
	return 0;
}