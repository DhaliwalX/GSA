// 
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <ctime>

// GSearchAlgo is General search algorithm of order o
int GSearchAlgo(int * A, int low, int high, int key, int o);

// quicksort algorithm for sorting an array A
void quicksort(int * , int , int );
int partiton(int *, int , int);
void start_work();
using namespace std;

// randomArray generates a random array of size n
// each element belongs to (min, max)
void randomArray(int * a, int n, int min, int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(min, max);
	for(int i = 0;i < n; i++)
		a[i] = dist(gen);
}

int main(){
    start_work();
	return 0;
}

void start_work(){
	ofstream fout;										// create a file stream object
	int arr[2500];
	char file[10] = "algok.csv";
	fout.open(file, ios::out | ios::app);				// create and open the file algok.csv
	int key, n;
	double progress = 0.0;
	std::clock_t start;
	for(n = 50; n <= 2500; n += 50)						// first row will consist of value of n
		fout << n << ",";
	fout << endl;
	double duration, sum = 0.0, _average = 0.0, avg = 0.0;
	for(int d = 2; d < 12; d++){						// loop through no. of partitions / order
		_average = 0.0;
		progress = 0.0;
		
		for(n = 50; n <= 2500; n += 50){				
			sum = 0.0;
			for(int k = 1; k <= 1000; k++){
				randomArray(arr, n, 1, n * 2);			// generate random array
				randomArray(&key,1, 1, n * 2);				// generate random key
				quicksort(arr, 0, n - 1);				// sort the array
				avg = 0.0;
				for(int l = 0; l < 100; l++){			// for smoothness of curve and increasing accuracy
					start = std::clock();
					GSearchAlgo(arr, 0, n - 1, key, d);
					duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;	// calculate duration
					avg += duration;
				}
				avg = avg / 100;
				sum += avg;
			}
			_average = sum / 1000;
			progress = ((double)n - 50.0) / 24.50; 
			system("clear");
			cout << "Order going on: "<< d << endl;
			cout << progress << "%" <<  endl;
			fout << _average << ",";					// write the averages to the file
		}
		fout << endl;	
	}
	fout.close();										// close the file
}


// definition of GSearchAlgo()
int GSearchAlgo(int * A, int low, int high, int key, int o){
	int mid, i;
	if((high - low + 1) > o){											// array is of size greater than order o
		
			mid = int((high - low + 1) / o);							// find mid
			if(key == A[low])
				return low;
			
			for(i = 1; i < o; i++)
				if(A[low + (mid * i)] == key)							// check at all partition point
					return low + mid * i;
			if(key == A[high])
				return high;
			if(key > A[low] && key < A[low + mid])						// key is in first partition
				return GSearchAlgo(A, low, low + mid - 1, key, o);	
			
			for(i = 1; i < o - 1; i++)
				if(key > A[low + mid * i] && key < A[low + mid * (i + 1)])	
					return GSearchAlgo(A, low + (mid * i) + 1, low + (mid * (i + 1)) - 1, key, o);

			if(key > A[ low + mid * (o - 1)] && key < A[high])			// key is in last partition
				 return GSearchAlgo(A, low + mid * (o - 1) + 1, high, key, o);

	}
	else {
		for(int i = low; i <= high; i++) 								// linear search if -(low - high) < k
			if(A[i] == key)
				return i;
		return -1;
	}
}

int partition(int * A, int left, int right){
	const int mid = left + (right - left) / 2;
	const int pivot = A[mid];
	std::swap(A[mid], A[left]);
	int i = left + 1;
	int j = right;
	while(i <= j){
		while(i <= j && A[i] <= pivot)
			i++;
		while(i <= j && A[j] > pivot)
			j--;
		if(i < j){
			swap(A[i], A[j]);
		}
	}
	swap(A[i - 1], A[left]);
	return i - 1;
}

void quicksort(int * A, int l, int h){
	if(l < h){
		int p = partition(A, l, h);
		quicksort(A, l, p - 1);
		quicksort(A, p + 1, h);
	}
}
