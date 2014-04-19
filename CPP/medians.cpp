/*************************************************** 
 *medians.cpp
 * find the N biggest element in an unsorted array
 * input:
 * output:
 * author: Zebras Wen
 * date: 2012.09.27
 * version: 0.0
 **************************************************/
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
void partion(int* a, int lo, int hi, int&, int&);
int quicksort(int* a, int lo, int hi, int pos);
int quicksort(int* a, int lo, int hi, int pos) {
    if (lo >= hi) {
        if (lo == hi) {
            return a[lo];
        }
        else {
            return -1;
        }
    }
    int low = lo;  // two variables to store the 
    int high = lo; // position of duplicate elements
	partion(a, lo, hi, low, high);
    if (pos > low + 1 && pos < high + 1) {
        return a[low + 1];
    }
    if ( pos < low + 2) {
        return quicksort(a, lo, low, pos);
    }
    else {
        // pos = pos + (high - low - 2);
        return quicksort(a, high, hi, pos);
    }	
    // return 
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
#define N 10
int main() {
    int a[N];
    int pos = 7;
    cout<<"pos: "<<pos<<endl;
    srand(50000);
	for (int i = 0; i < N; i++) {
	    a[i] = rand() % N;
		cout<<a[i]<<" ";
	}
	cout<<endl;
	int a_pos = quicksort(a, 0, N - 1, pos);
	for (int i = 0; i < N; i++) {
	    cout<<a[i]<<" ";
	}
	cout<<endl;
    cout<<"a_pos: "<<a_pos<<endl;
    return EXIT_SUCCESS;
}
