#include<iostream>
#include<omp.h>
#include<ctime>

#define N 16
#define M 3
#define c 10

static int x[M][M]={
					{-1, -1, -1},
					{-1,  8, -1},
					{-1, -1, -1} };

static int arr[N][N] = {
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

using namespace std;

void apply_filter_on_image(int** image, int** filter, int** result, int tid, int scale = 255)
{
	int halfSize = int(M / 2);
	for (int i = 0; i < N; i++)//rows
	{
		if (i - halfSize <= 0 || i + halfSize >= N)
			continue;
		for (int j = 0; j < N ; j++)//column
		{
			if (j - halfSize <= 0 || j + halfSize >= N)
				continue;
			int filtertotal = 0;
			for (int k = 0; k < M; k++)
			{
				for (int l = 0; l < M; l++)
				{
					if (i + k >= 0 && i + k < N && j + l >= 0 && j + l < N)
					{
						int a = image[i + k][j + l];
						int b = filter[k][l];
						filtertotal += a * b;
					}
				}
			}
			result[i - int(M / 2)][j - int(M / 2)] = ((filtertotal + scale) % scale);//handle the resulted value to be between 0-255
		}
	}
}

int main()
{
	int** image = 0;
	image = new int* [N];
	int** filter = 0;
	for (int i = 0; i < N; i++)
	{
		image[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			image[i][j] = arr[i][j];
		}
	}
	filter = new int* [M];
	for (int i = 0; i < M; i++)
	{
		filter[i] = new int[M];
		for (int j = 0; j < M; j++)
		{
			filter[i][j] = x[i][j];
		}
	}
	int** result = 0;
	result = new int* [N - (M - 1)];
	for (int h = 0; h < N - (M - 1); h++)
	{
		result[h] = new int[N - (M - 1)];

		for (int w = 0; w < N - (M - 1); w++)
		{
			result[h][w] = 0;
		}
	}


	double  wt1 = omp_get_wtime();
	#pragma omp parallel
	{
		int tid=omp_get_thread_num();
		apply_filter_on_image(image, filter, result, 255,tid);
	}
	double  wt2 = omp_get_wtime();
	
	
	cout << "[ ";
	for (int i = 0; i < N - (M - 1); i++)
	{
		cout << "[ ";
		for (int j = 0; j < N - (M - 1); j++)
		{
			cout << result[i][j] << ",";
		}
		cout << "]," << endl;
	}
	cout << "]" << endl;
	cout << "time = " << (wt2 - wt1) << endl;
	system("pause");
}