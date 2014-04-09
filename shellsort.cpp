#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void shellsort(int* a, int len) {
    int h = 1;
	while(h < len) h = 3*h + 1;
	while(h > 0) {
	   for (int i = h; i < len; i++) {
	       for (int j = i; j >= h && a[j] < a[j-h]; j -= h) {
		       int tmp = a[j];
			   a[j] = a[j-h];
			   a[j-h] = tmp;
		   }
	   }
        h = h/3;
	}
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
	shellsort(a, N);
	for (int i = 0; i < N; i++) {
	    cout<<a[i]<<" ";
	}
	cout<<endl;
    return EXIT_SUCCESS;
}
