#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
void partion(int* a, int lo, int hi, int&, int&);
void quicksor(int* a, int lo, int hi);
void quicksort(int* a, int lo, int hi) {
    if (lo >= hi) {
	    return;
    }
    int low = lo;  // two variables to store the 
    int high = lo; // position of duplicate elements
	partion(a, lo, hi, low, high);
	quicksort(a, lo, low);
	quicksort(a, high, hi);
}

void partion(int* a, int lo, int hi, int &low, int &high) {
    int pivot = a[lo]; // choose leftmost element as pivot
	int curIndex = lo;
	int i = lo;
	int j = hi;
	while (i < j+1) {
	    if (a[i] < pivot) {
		    // we keep update the curIndex of pivot position
			// in 3-way quicksort, the position of pivot is changed
			// after each exchange.
			a[curIndex] = a[i];
			a[i] = pivot;
			i++;
			curIndex++;
		}
		else if (a[i] > pivot){
		    // we exchange no matter what the element at
			// the end is, we are sure the element exhanged to the
			// end is larger than the pivot.
		    int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			j--;
		}
		else {
		    // curIndex++;
			i++;
		}
	}
    low = curIndex - 1; // lower bound of duplicate elements
    high = i;           // upper bound
	// return curIndex;
}
#define N 30
int main() {
    int a[N];
    srand(50000);
	for (int i = 0; i < N; i++) {
	    a[i] = rand() % N;
		cout<<a[i]<<" ";
	}
	cout<<endl;
	quicksort(a, 0, N - 1);
	for (int i = 0; i < N; i++) {
	    cout<<a[i]<<" ";
	}
	cout<<endl;
    return EXIT_SUCCESS;
}
