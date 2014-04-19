/****************************************************************
 * mergesort.cpp
 * sort an input using merging sort.
 * author: Zebras Wen
 * date: 2012.09.28
 * version: 0.0
 * reference:
 ***************************************************************/
 
 #include<iostream>
 #include<cstdlib>
 #include<ctime>
 using namespace std;
 #define N 10 // number of element to sort
 
 template<class T>
 void merge(T* a, int lo, int hi);
 
 template<class T>
 void mergesort(T* a, int lo, int hi);
 
 template<class T>
 void mergesort(T* a, int lo, int hi) {
    if (lo == hi) {
        return;
    }
    int mid = (lo + hi) / 2;
    mergesort<T>(a, lo, mid);
    mergesort<T>(a, mid + 1, hi);
    merge<T>(a, lo, hi);
    // for (int i = 0; i < 10; i++) {
        // cout<<a[i]<<" ";
    // }
    // cout<<endl;
 }
 
 template<class T>
 void merge(T* a, int lo, int hi) {
    int mid = (lo + hi) / 2;
    T* b = new T[mid - lo + 1]; 
    // make a copy of the first half data
    for (int i = 0, j = lo; j < mid + 1; i++, j++) {
        b[i] = a[j];
    }
    // merge element from lo->mid and mid + 1->hi
    int i = 0;
    int j = mid + 1;
    int k = lo;
    // bool isExchanged = false;
    while (k < hi + 1) {
        if (i < mid - lo + 1 && j < hi + 1) {
            if (b[i] <= a[j]) {
                a[k++] = b[i++];
            }
            else {
                a[k++] = a[j++];
            }
            continue;
        }
        if (i == (mid - lo + 1)) {
            a[k++] = a[j++];
        }
        else {
            a[k++] = b[i++];
        }
    }
    delete[]b;
 }
 
 
 int main(int argc, char* args[]) {
    double aa[N];
    srand(unsigned(time(0)));
    for (int i = 0; i < N; i++) {
        aa[i] = rand()/double(RAND_MAX)*N;
    }
    mergesort<double>(aa, 0, N - 1);
    for (int i = 0; i < N; i++) {
        cout<<aa[i]<<" ";
    }
    cout<<endl;
 }