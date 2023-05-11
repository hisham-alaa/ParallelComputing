#include<iostream>
#include<omp.h>
using namespace std;

long fib(int n){
    if(n < 2) return n;
    else{
        int a, b;
        #pragma omp task shared(a) if (n > 30)
            a = fib(n - 1);
        #pragma omp task shared(b) if (n > 30)
            b = fib(n - 2);
        #pragma omp taskwait
            return a + b;
    }
}

long fib_Seq(int n){
    if(n < 2) return n;
    else{
        int a, b;
        a = fib(n - 1);
        b = fib(n - 2);
        return a + b;
    }
}
int main(){
    int fibs[40];
    fibs[0] = 0;
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        for (int i = 1; i <= 40; i++){
            #pragma omp single
            fibs[i] = fib(i); 
        }
        
    }
    double end = omp_get_wtime();
    cout<<"\nTime (in sec): "<<(end - start)<<endl;
    for (int i = 1; i <= 40; i++){
        cout<<fibs[i]<<" ";
    }

    // Sequential Part
    // not require but to compare difference
    // it take (36 sec)
    int fibs_seq[40];
    fibs_seq[0] = 0;

    double start_seq = omp_get_wtime();
    for (int i = 1; i <= 40; i++)
        fibs_seq[i] = fib_Seq(i); 
    double end_seq = omp_get_wtime();
    
    cout<<"\nTime seq(in sec): "<<(end_seq - start_seq)<<endl;
    for (int i = 1; i <= 40; i++){
        cout<<fibs_seq[i]<<" ";
    }
    
    
    return 0;
}