#include <iostream>
#include <omp.h>
using namespace std;

void createArray(long arr[], long size)
{
	for (long i = 0; i < size; i++)
	{
		arr[i] = i + 1;
	}
}

void printArray(long arr[], long size)
{
	cout << "[";
	for (long i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "]" << endl;
}

int main()
{
	const int size = 11;
	long arr[size];

	//Create and print array
	createArray(arr, size);
	printArray(arr, size);

	//Calculate sum
	int currentSize = size;
	while (currentSize > 1)
	{
		int tmp = currentSize / 2;
		#pragma omp parallel for num_threads(tmp)
		for (long i = 0; i < tmp; i++)
		{
			arr[i] += arr[currentSize - i - 1];
			cout << "Sum of elements with indices " << i << " and " << currentSize - i - 1 << ": " << arr[i] << endl;
			cout << "Array after change: ";
			printArray(arr, currentSize);
			cout << endl;
		}
		currentSize = currentSize / 2 + currentSize % 2;
	}

	cout << "Total sum of elements: " << arr[0] << endl;
}