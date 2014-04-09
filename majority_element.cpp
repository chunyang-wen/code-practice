// returns -1 if there is no element that is the majority element, otherwise that element

// funda :: if there is a majority element in an array, say x, then it is okay to discard 
// a part of that array that has no majority element, the remaining array will still have
// x as the majority element

// worst case complexity :  O(n)

int findMajorityElement(int * arr, int size) { 
     int count = 0, i, majorityElement;
     for (i = 0 ; i < size ; i++) {
        if (count == 0) {
            majorityElement = arr[i];
        }
        if(arr[i] == majorityElement) 
           count++;
        else 
           count--;
     }
     count = 0;
     for (i = 0; i < size; i++) {
          if (arr[i] == majorityElement) {
                count++;
          }
     if (count > size/2) {
          return majorityElement;
     }
     else return -1;
}