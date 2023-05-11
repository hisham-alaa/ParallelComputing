#include <iostream>
#include <pthread.h>
#include <ctime>
using namespace std;

//// AT TIME 0.001 for 10*10= 100 element

//used Variables 
#define threadsNo 4
const long rawsNO = 10;
const long columnsNo = 10;
long  mat1[rawsNO][columnsNo], mat2[rawsNO][columnsNo];
long  allSum[rawsNO][columnsNo];
long  allSub[rawsNO][columnsNo];
int len = rawsNO/threadsNo;  // Divid raws only 
int remLen = rawsNO % threadsNo;

//Summation function
void* operat(void* arg){ 
	int id = (int)arg;
	int start,end;

	if(id != threadsNo-1){
		start = id * len;
		end = start + len;
	}else{
		start = rawsNO - (remLen + len);
		end = start + (remLen + len);
	}

	for(int i= start ; i<end ;i++){
		// for each partition of raws will loop all columns 
		for(int j=0 ; j<columnsNo ;j++){
			allSum[i][j] = mat1[i][j] + mat2[i][j];
			allSub[i][j] = mat1[i][j] - mat2[i][j];
		}
	}

	pthread_exit(NULL);
	return NULL;
}

void main(){

	clock_t t1,t2;
	//Vectors creation
	for(int i=0 ; i<rawsNO ; i++){
		for(int j=0 ; j<columnsNo ;j++){
		mat1[i][j] =2;
		mat2[i][j] =1;
		}
	}
	
	

	//Create threads
	t1 = clock();
	pthread_t myThreads[threadsNo];
	for(int i=0 ; i<threadsNo ; i++)
		pthread_create(&myThreads[i], NULL,*operat, (void*)i);
	
	for(int i=0 ; i<threadsNo ; i++)
		pthread_join(myThreads[i], NULL);
	t2 = clock();

	//Display Output
	cout<<"All Sum = " <<endl;
	for(int i=0 ; i<rawsNO; i++){
		for(int j=0 ; j<columnsNo ; j++){
			cout<<allSum[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"All Sub = " <<endl;
	for(int i=0 ; i<rawsNO; i++){
		for(int j=0 ; j<columnsNo ; j++){
			cout<<allSub[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<" At time: "<<(double)(t2-t1)/CLOCKS_PER_SEC<<endl;
	system("pause");
	pthread_exit(NULL);
}