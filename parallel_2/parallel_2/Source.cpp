#include<iostream>
#include<omp.h>
#include<ctime>

using namespace std;
int* fib;
int fibo(int i) {
	if (fib[i] == -1)
		return fibo(i - 1) + fibo(i - 2);
	return fib[i];
}
int main() {
	int n;
	cout << "enter the fibonachi you want" << endl;
	cin >> n;
	fib = new int[n];
	for (int i = 3; i < n; i++)
		fib[i] = 0;
	fib[0] = 0;
	fib[1] = fib[2] = 1;
	#pragma omp parallel for
	for (int i = 3; i < n; i++)
		fib[i]=fib[i-1]+fib[i-2];

	cout << "value of fibonachi " << n << " is " << fib[n];


	return 0;
}
















/*
#include <iostream>
#include <omp.h>
#include <ctime>
using namespace std;

int main()
{
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		printf("hello world from thread %d \n", id);
	}

	return 0;
}
*/


/*
#include<iostream>
#include<omp.h>
#include<ctime>

using namespace std;
int main()
{

	clock_t t1 = clock();
	int id, nth,res=0,sum,n=10000,len;
	int *arr = new int[n];
	for (int i = 0; i < n; i++)
		arr[i] = i+1;
	#pragma omp parallel num_threads(4) private(id,sum) shared(nth,n,arr,res,len)
	{
		sum = 0;
		id = omp_get_thread_num();

		#pragma omp single
		{
			nth = omp_get_num_threads();
			len = n / nth;
		}
		for (int i = id*len ; i < (id+1)*len ; i++)
		{
			sum += arr[i];
		}

		#pragma omp critical
		{
			//cout << "hello world " << id << " of " << nth <<endl;
			cout << "result in thread " << id << " is " << sum<<"\n";
			res += sum;
		}
	}

	clock_t t2 = clock();

	cout << "result is " << res << "\n";
	cout << "time is " << double(t2-t1)/CLOCKS_PER_SEC << "\n";
	cout << "result must be " << (n* (n - 1)) / 2;

	return 0;
}
*/
/*

#include<iostream>
#include<omp.h>
#include<time.h>

using namespace std;

int arr[100000000];


void main() {
	clock_t startT = clock();

	#pragma omp parallel for
		for (int i = 0; i < 100000000; i++)
			arr[i] = i;



	printf("time taken : %.3fs\n", (double)(clock() - startT)/CLOCKS_PER_SEC);

	system("pause");
}*/