#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
	int numberOfParts = 4;
	const int size = 10;
	long arr[size];

	//Create and print array
	cout << "[";
	for (long i = 0; i < size; i++)
	{
		arr[i] = i + 1;
		cout << arr[i] << " ";
	}
	cout << "]" << endl;

	//Calculate sum
	int sum = 0;
	int leftIndex = 0;
	int delta = size / numberOfParts;
	if (size % numberOfParts == 0) {
		delta -= 1;
	}

	for (int i = 0; i < numberOfParts - 1; i++) {
		#pragma omp parallel for reduction(+:sum)
		for (int i = leftIndex; i <= leftIndex + delta; i++) {
			sum += arr[i];
		}
		cout << "Sum of current chunk with left index " << leftIndex << " and right index " << leftIndex + delta << ": " << sum << endl;
		leftIndex += (delta + 1);
	}
	if (size > leftIndex) {
		for (int i = leftIndex; i <= size - 1; i++) {
			sum += arr[i];
		}
		cout << "Sum of current chunk with left index " << leftIndex << " and right index " << leftIndex + delta << ": " << sum << endl;
	}
	cout << "Total sum of elements: " << sum << endl;
}