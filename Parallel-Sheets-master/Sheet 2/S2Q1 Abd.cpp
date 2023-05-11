#include<iostream>
#include<omp.h>
using namespace std;
#define Numth 6
#define size 100
int main(){
    long long *fibs = new long long [size];
    fibs[0] = 1;
    fibs[1] = 1;
    int numFib = 60;
    #pragma omp parallel num_threads(Numth)
    {
        #pragma omp for schedule(dynamic,10)
        for (int i = 2; i <= numFib; i++)
        {
            fibs[i] = fibs[i-1] + fibs[i-2];
        }
    }
    cout<<"\n";
    for (int i = 1; i <= numFib; i++)
        {
            cout<<fibs[i]<<" ";
        }
    cout<<"\n";
    return 0;
}