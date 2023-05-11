#include <iostream>
#include <pthread.h>
#include <ctime>
using namespace std;

//// AT TIME 0.001 for 80000000 element

//used Variables
#define threadsNo 4
const long elementsNO = 80000000;
pthread_mutex_t myLock;
long  vector1[elementsNO], vector2[elementsNO];
long  allSum=0;
int len = elementsNO/threadsNo;
int remLen = elementsNO % threadsNo;

//Summation function
void* Summation(void* arg){ 
	int id = (int)arg;
	long  partialSum = 0;
	int start,end;

	if(id != threadsNo-1){
		start = id * len;
		end = start + len;
	}else{
		start = elementsNO - (remLen + len);
		end = start + (remLen + len);
	}

	for(int i= start ; i<end ;i++){
		partialSum += vector1[i]*vector2[i];
	}
	pthread_mutex_lock(&myLock);
	cout<<"partial sum: "<<partialSum<<" ,thread: "<<id<<" ,start: "<<start<<" ,end: "<<end<<endl;
	pthread_mutex_unlock(&myLock);

	pthread_mutex_lock(&myLock);
	allSum += partialSum;
	pthread_mutex_unlock(&myLock);
	pthread_exit(NULL);
	return NULL;
}

void main(){

	clock_t t1,t2;
	//Vectors creation
	for(int i=0 ; i<elementsNO ; i++){
		vector1[i]=1;
		vector2[i]=1;
	}
	
	//Mutex creation
	pthread_mutex_init(&myLock,NULL);

	//Create threads
	t1 = clock();
	pthread_t myThreads[threadsNo];
	for(int i=0 ; i<threadsNo ; i++)
		pthread_create(&myThreads[i], NULL,*Summation, (void*)i);
	t2 = clock();
	for(int i=0 ; i<threadsNo ; i++)
		pthread_join(myThreads[i], NULL);

	cout<<"All Sum = " <<allSum <<" ,At time: "<<(double)(t2-t1)/CLOCKS_PER_SEC<<endl;
	pthread_mutex_destroy(&myLock);
	system("pause");
	pthread_exit(NULL);
}