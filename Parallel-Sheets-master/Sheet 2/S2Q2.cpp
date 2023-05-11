#include<iostream>
#include<omp.h>
using namespace std;
#define SIZE 10000
#define threadsNo 6

int main(){
    double start;
    double end;

    // creation 2D dynamic Array
    int **A = new int*[SIZE];
    int **B = new int*[SIZE];
    int **C = new int*[SIZE];
    for (int i = 0; i < SIZE; i++){
        A[i] = new int[SIZE];
        B[i] = new int[SIZE];
        C[i] = new int[SIZE];
    }

    // Intialization Array
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }
    

    // Parallel Task
    start = omp_get_wtime();
    #pragma omp parallel for collapse(3) num_threads(threadsNo)
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++)
                C[i][j] = A[i][k] * B[k][i];            
    end = omp_get_wtime();

    /* if want to display result
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            cout<<C[i][j]<<" ";
        }
        cout<<"\n";
    }
    */
    cout<<"\nTime (in sec): "<<(end - start)<<endl;
    

    return 0;
}