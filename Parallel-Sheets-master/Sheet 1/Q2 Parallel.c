#include <iostream>
#include <pthread.h>
#include <ctime>
using namespace std;

// AT TIME 0.026 for 1M element


//used Variables
#define threadsNo 60
#define elementsNO 1000000
int myVector[elementsNO];
long allSum = 0;
int len = elementsNO/threadsNo; 
int remLen = elementsNO % threadsNo; 
pthread_mutex_t myLock;


//Summation function
void* Summation(void* arg){ 
	int partialSum = 0, id = (int)arg;
	int start,end;
	//interval
	if(id != threadsNo-1){
		 start = id*len;
		 end = start+len;
	}
	else if (id == threadsNo -1){
		start = elementsNO-(remLen+len);
		end = start+(remLen+len);
	}
	for(int i=start ; i<end ; i++)
		partialSum += myVector[i];

	pthread_mutex_lock(&myLock);
	allSum += partialSum; 
	pthread_mutex_unlock(&myLock);

	pthread_exit(NULL);
	return NULL;
}

void main(){

	clock_t t1,t2;

	//Mutex creation
	pthread_mutex_init(&myLock,NULL);
	//vector intialization
	for(int j=0 ; j< elementsNO; j++)
		myVector[j] =j;

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