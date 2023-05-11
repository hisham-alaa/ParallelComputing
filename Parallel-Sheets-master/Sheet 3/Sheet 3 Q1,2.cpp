#include<iostream>
#include<math.h>
#include<vector>
#include<omp.h>
using namespace std;

// *compilation line*
// g++ [FILE_NAME].cpp -fopenmp -o out.exe
// *run command*
// out.exe

//int n = 6;
//int arr[] = {9,3,7,2,1,8};

long n = 100000000; // 8 0's
int *arr = new int[n];

int par_qsort(int *data, int lo, int hi)
{
    if (lo > hi) return 0;
    int l = lo;
    int h = hi;
    int p = data[(hi + lo) / 2];
	int count = 0;
    while (l <= h)
    {
        while (data[l] < p) l++;
        while (data[h] > p) h--;
        if (l <= h)
        {
			if(l < h)
				count++;
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            l++;
            h--;
        }
    }

	/*
		-The clause final is used to prevent creating new tasks 
		for parts of array that contain less than n/100 elements.

		-The threshold n/100 has been chosen experimentally.
	*/
	int lcount, hcount;
	#pragma omp task shared(lcount) final(h - lo < n/100)
	lcount = par_qsort(data, lo, h);
    #pragma omp task shared(hcount) final(hi - l < n/100)
	hcount = par_qsort(data, l, hi);

	#pragma omp taskwait
	return count + lcount + hcount;
}

int qsort(int *data, int lo, int hi)
{
    if (lo > hi) return 0;
    int l = lo;
    int h = hi;
    int p = data[(hi + lo) / 2];
	int count = 0;
    while (l <= h)
    {
        while (data[l] < p) l++;
        while (data[h] > p) h--;
        if (l <= h)
        {
			
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
			if(l < h){
				count++;
				/*for(int i = 0; i < n; i++)
					cout << data[i] << " ";
				cout << endl;*/
			}
            l++;
            h--;
        }
    }
	int lcount, hcount;
	lcount = qsort(data, lo, h);
	hcount = qsort(data, l, hi);

	return count + lcount + hcount;
}

int main()
{	
	
	for(int i = 0; i < n; i++)
		arr[i] = n-i-1;

	/*for(int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;*/

	double wt1 = omp_get_wtime();
	int c;
	int flag;
	cout << " Enter 0 for sequential and 1 for parallel: ";
	cin >> flag;
	if(flag){
		#pragma omp parallel
		#pragma omp single
		c = par_qsort (arr, 0,n-1);
	}
	/*
	else
		c = qsort (arr, 0,n-1);
	*/
	double wt2 = omp_get_wtime();

	cout << "# swaps = " << c << endl;
	cout << "Time = " << wt2-wt1 << endl;
	return 0;
}