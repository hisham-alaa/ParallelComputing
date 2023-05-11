/*
#include<iostream>
#include<pthread.h>
using namespace std;

pthread_mutex_t mute;

void* p(void* arg) {
	int id = (int)arg;
	pthread_mutex_lock(&mute);
	cout << "thread num " << id << endl;
	pthread_mutex_unlock(&mute);

	pthread_exit(NULL);
	return NULL;
}

void main() {

	pthread_t threadName[10]; //declare a thread
	
	pthread_attr_t attrName; //declare custom attribute
	pthread_attr_init(&attrName); // initialize our attr
	pthread_attr_setdetachstate(&attrName, PTHREAD_CREATE_DETACHED);//set the detach state whether detached or joinable

	pthread_mutex_init(&mute, NULL);

	for(int i=0;i<10;i++)
		if(i%2==0)
			pthread_create(&threadName[i],&attrName,*p,(void*)i);
		else 
			pthread_create(&threadName[i], NULL, *p, (void*)i);

	// to create thread the method takes 4 args the thread address,the 
	// attribute whether detached or joinable , the method and the args
	// for you method you want it to be done in parallel

	for (int i = 0; i < 10; i++)
		pthread_join(threadName[i],NULL);

	// the calling thread is the thread which this call used in its body
	// so this is called for main thread which means that what after this 
	// calling won't be executed til the argument thread finish
	// (we cannot use it untill our thread attribute is joinable). 

	cout << "Hello world All Done " << endl;

	
	//* now we have
	//* pthread_t declare thread
	//* pthread_create() create the thread
	//* pthread_attr_t declare attr
	//* pthread_attr_init()
	//* pthread_attr_setdetachstate()
	//* pthread_join()
	//* pthread_attr_destroy()
	//* pthread_mutex_t
	//* pthread_mutex_init()
	//* pthread_mutex_lock()
	//* pthread_mutex_unlock()
	//* pthread_mutex_destroy()
	//* pthread_exit()


	pthread_mutex_destroy(&mute);
	pthread_attr_destroy(&attrName);
	system("pause");
	pthread_exit(NULL);
}
*/




/*							// Question 1
#include<iostream>
#include<pthread.h>
using namespace std;

pthread_mutex_t myMutex;

void* printHello(void* args)
{
	int id = (int)args;

	pthread_mutex_lock(&myMutex);
	cout << "Hello new parallel programmer from thread : " << id << "\n";
	pthread_mutex_unlock(&myMutex);

	pthread_exit(NULL);
	return NULL;
}

void main() {

	pthread_mutex_init(&myMutex, NULL);
	pthread_t myThread[8];

	for (int i = 0; i < 8; i++) {
		pthread_create(&myThread[i], NULL, *printHello, (void*)i);
	}

	system("pause");
	pthread_exit(NULL);
}
*/




/*							// Question 2
#include<iostream>
#include<pthread.h>
using namespace std;

float sum = 0;
int a[160];

pthread_mutex_t myMutex;
void* printHello(void* args)
{
	int id = (int)args;
	float mysum = 0;
	for (int i = id * 10; i < ((id + 1) * 10); i++)
		mysum += a[i];
	pthread_mutex_lock(&myMutex);
	cout << "summation of thread : " << id << " is : " << mysum << endl;
	sum += mysum;
	if (id == 15)
		cout << "result is : " << sum << "\n";
	pthread_mutex_unlock(&myMutex);
	pthread_exit(NULL);
	return NULL;
}

void main() {

	for (int i = 0; i < 160; i++)
		a[i] = i + 1;


	pthread_mutex_init(&myMutex, NULL);
	pthread_t myThread[16];

	for (int i = 0; i < 16; i++) {
		pthread_create(&myThread[i], NULL, *printHello, (void*)i);
	}

	system("pause");
	pthread_exit(NULL);
}
*/




/*							// Question 3
#include<iostream>
#include<pthread.h>
using namespace std;

long product = 0,sum=0;
int arr1[160];
int arr2[160];
int counter = 0;

pthread_mutex_t myMutex;
void* printHello(void* args)
{
	int id = (int)args;
	float mysum = 0;
	for (int i = id * 10; i < ((id + 1) * 10); i++)
		mysum += (arr1[i] * arr2[i]);
	pthread_mutex_lock(&myMutex);
	cout << "dot product for thread : " << id << " is : " << mysum << endl;
	product += sum;
	counter++;
	if (counter == 16)
		cout << "result is : " << product << "\n";
	pthread_mutex_unlock(&myMutex);
	pthread_exit(NULL);
	return NULL;
}

void main() {

	for (int i = 0; i < 160; i++)
	{
		arr1[i] = (rand() % 100) + 1;
		arr2[i] = (rand() % 100) + 1;
	}

	pthread_mutex_init(&myMutex, NULL);
	pthread_t myThread[16];

	for (int i = 0; i < 16; i++) {
		pthread_create(&myThread[i], NULL, *printHello, (void*)i);
	}

	system("pause");
	pthread_exit(NULL);
}
*/




/*							// Assignment 1
#include<iostream>
#include<pthread.h>
using namespace std;

int arr1[160][160];
int arr2[160][160];
int sum[160][160];
int sub[160][160];

int counter = 0;

pthread_mutex_t myMutex;

void* printHello(void* args)
{
	int id = (int)args;
	for (int i = id * 10; i < ((id + 1) * 10); i++)
	{
		for (int j = 0; j < 160; j++)
		{
			sum[i][j] = arr1[i][j] + arr2[i][j];
			sub[i][j] = arr1[i][j] - arr2[i][j];
		}
	}

	pthread_mutex_lock(&myMutex);
	cout << "thread " << id << " has finished\n";
	counter++;
	if (counter == 16)
	{
		int x = rand() % 100;
		int y = rand() % 100;

		cout << "to check results \n";
		cout << "summation " << arr1[x][y] << " + " << arr2[x][y] << " = " << sum[x][y] << "\n";
		cout << "subtraction " << arr1[x][y] << " - " << arr2[x][y] << " = " << sub[x][y] << "\n";
	}
	pthread_mutex_unlock(&myMutex);
	pthread_exit(NULL);
	return NULL;
}

void main() {

	for (int i = 0; i < 160; i++)
		for (int j = 0; j < 160; j++)
		{
			arr1[i][j] = (rand() % 100) + 1;
			arr2[i][j] = (rand() % 100) + 1;
		}


	pthread_mutex_init(&myMutex, NULL);
	pthread_t myThread[16];

	for (int i = 0; i < 16; i++) {
		pthread_create(&myThread[i], NULL, *printHello, (void*)i);
	}

	system("pause");
	pthread_exit(NULL);
}
*/




/*
#include<iostream>
#include<pthread.h>
#include<ctime>
using namespace std;

int arr1[160][160];
int arr2[160][160];
int product[160][160];

void matMultiplicationseq()
{
	int mysum = 0;
	for (int i = 0; i < 160; i++)
	{
		for (int j = 0; j < 160; j++)
		{
			for (int k = 0; k < 160; k++)
				mysum += (arr1[i][k] * arr2[k][j]);
			product[i][j] =mysum;
		}
	}
}

void* matMultiplication(void* args)
{
	int id = (int)args;
	int mysum = 0;
	
	for (int i = id * 10; i < ((id + 1) * 10); i++)
	{
		for (int j = 0; j < 160; j++)
		{
			for (int k =0; k< 160; k++)
				mysum += (arr1[i][k]*arr2[k][j]);
			product[i][j] = mysum;
		}
	}

	pthread_exit(NULL);
	return NULL;
}

int main(){

	for (int i = 0; i < 160; i++)
		for (int j = 0; j < 160; j++)
		{
			arr1[i][j] = (rand() % 100) + 1;
			arr2[i][j] = (rand() % 100) + 1;
		}

	pthread_t myThread[16];
		
	clock_t end, start = clock();
	for (int i = 0; i < 16; i++) 
		pthread_create(&myThread[i], NULL, *matMultiplication, (void*)i);
	end = clock();
	
	for (int i = 0; i < 16; i++)
		pthread_join(myThread[i], NULL);

	cout << "time taken by parallel product is " << (double)(end - start) / CLOCKS_PER_SEC<<endl;

	start = clock();
	matMultiplicationseq();
	end = clock();

	cout << "time taken by sequential product is " << (double)(end - start) / CLOCKS_PER_SEC<<endl;

	system("pause");
	pthread_exit(NULL);
	return 0;
}
*/