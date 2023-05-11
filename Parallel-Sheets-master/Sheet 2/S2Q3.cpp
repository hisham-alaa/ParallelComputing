#include<iostream>
#include<omp.h>
using namespace std;
//#define num 10000
#define threadsNo 6

int main(){
    int startInt, endInt, len;
    long long sum = 0;
    double start, end;
    cout<<"[+] Enter start of interval\n";
    cout<<">>> ";
    cin>>startInt;
    cout<<"[+] Enter end of interval\n";
    cout<<">>> ";
    cin>>endInt;

    // Get length of my interval
    // +1 here b/c start count from 0 and interval
    // ex: [10 : 20 ] >>> 10 + 11 + ... + 20  
    len = endInt - startInt;
    int* arr = new int[len+1];

    // store this interval in array
    for(int i=0; i<= len; i++){
        arr[i] = startInt++;
    }
    
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) num_threads(threadsNo)
    for(int i=0; i<= len; i++){
        sum += arr[i];
    }
    end = omp_get_wtime();
    cout<<"\nSum: "<<sum<<endl;
    cout<<"Time (in sec): "<<(end - start)<<endl;
    return 0;
}