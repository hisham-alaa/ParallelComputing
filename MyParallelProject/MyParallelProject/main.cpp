#include<iostream>
#include<omp.h>
#include<ctime>

using namespace std;

int* arr;//global array to be accessed by all methods

void sequentialSearch(int n,int value) {

	for (int i = 0; i < n; i++) {
		if (arr[i] == value)
		{
			cout << "the Searched num found at index " << i << endl;
			break;
		}
	}

}

clock_t parallelSearch(int n, int value){
	int v = 0;
	clock_t c=clock();
	#pragma omp parallel private (c)
	{
		#pragma omp for schedule(dynamic,n/omp_get_num_threads())
		for (int i = 0; i < n; i++) {
			if (arr[i] == value)
			{
				cout << "the Searched num found by thread " << omp_get_thread_num()
					<<" at index "<<i << endl;
				c=clock();
			}
		}
	}
	return c;
}

int main() {
	int n = 0, value = 0, index = 0;
	cout << "Enter size of the array" << endl;
	cin >> n;
	arr = new int[n];
	cout << "Enter value you want (Greater than or equal 100)" << endl;
	cin >> value;
	cout << "Enter index to put the value in it (less than the size)" << endl;
	cin >> index;

	for (int i = 0; i < n; i++)
		arr[i] = (i==index)?(value):(rand() % 100);

	clock_t end, start = clock();
	sequentialSearch(n,value);
	end = clock();
	cout << "time of sequential algorithm is "
		 << (double)(end-start) / CLOCKS_PER_SEC << endl<<endl;
	
	start = clock();
	end=parallelSearch(n, value);
	
	cout << "time of Parallel algorithm is " 
		 << (double)(end-start) / CLOCKS_PER_SEC << endl<<endl;

	return 0;
}