#include<iostream>
#include<math.h>
#include<omp.h>
using namespace std;

// Vector that will be sorted
long n = 5; // 8 0's
int *arr = new int[n];

// function to sort and count swaps
int qsort(int *data, int lo, int hi){
    
    if(lo > hi) return 0;
    int l = lo;
    int h = hi;
    int p = data[(l + h)/2];
    int count = 0;
    while(l <= h){
        while(data[l] < p) l++;
        while(data[h] > p) h--;
        if(l <= h){
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            if(l < h)
                count++;
            l++;
            h--;
        }   
    }
    int lcount, hcount;
    #pragma omp task shared(lcount) final(h - lo < n/100)
	lcount = qsort(data, lo, h);
    
    #pragma omp task shared(hcount) final(hi - l < n/100)
	hcount = qsort(data, l, hi);

	#pragma omp taskwait
	return count + lcount + hcount;
}


int main(){
    int c;
    // Intialize Array w/ worst case
    for(int i = 0; i < n; i++)
		arr[i] = n-i-1;

    double wt1 = omp_get_wtime();
    #pragma omp parallel
	#pragma omp single
	c = qsort (arr, 0,n-1);
    double wt2 = omp_get_wtime();

    cout << "# swaps = " << c << endl;
	cout << "Time = " << wt2-wt1 << endl;
    return 0;
}