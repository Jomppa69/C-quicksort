#include <iostream>

using namespace std;

// Standard recursive quicksort algorithm.
void quicksort(int a[], int left, int right) {
    int i, j, v, temp;
    if (right - left > 0) { // at least two items in the partition
        v = a[right]; // v is pivot
        i = left -1; // 1 to the left of beginning
        j = right; // 1 to the right of where search starts
        while (true) {
            while(a[++i] < v); // pre-increment i until a[i] is >= pivot
            while(a[--j] > v); // pre-decrement j until a[i] is <= pivot
            if(i >= j) break; // if i and j have crossed -- get out of loop
            temp = a[i]; // otherwise, swap a[i] and a[j]
            a[i] = a[j];
            a[j] = temp;
        }
        a[right] = a[i]; // i and j have crossed, so swap a[i] and the pivot
        a[i] = v;
        // the pivot is now in place at i; now call quicksort on the partitions
        quicksort(a, left, i-1); // left partition
        quicksort(a, i+1, right); // rightpartition.
    }
}


// Quicksort algorithm with median of 3
void quicksort3m(int a[], int left, int right) {
    int i, j, v, temp;
    if (right - left > 0) { // at least two items in the partition
         // Median of three elements
        int middle = left + (right - left) / 2;
        if (a[left] > a[middle]) // if left is larger than middle swap them.
            swap(a[left], a[middle]);
        if (a[left] > a[right]) // if left is larger than right swap them.
            swap(a[left], a[right]);
        if (a[middle] > a[right]) // if middle is larger than right swap them.
            swap(a[middle], a[right]);
        v = a[middle]; // v is pivot
        i = left -1; // 1 to the left of beginning
        j = right; // 1 to the right of where search starts
        while (true) {
            while(a[++i] < v); // pre-increment i until a[i] is >= pivot
            while(a[--j] > v); // pre-decrement j until a[i] is <= pivot
            if(i >= j) break; // if i and j have crossed -- get out of loop
            temp = a[i]; // otherwise, swap a[i] and a[j]
            a[i] = a[j];
            a[j] = temp;
        }
        a[right] = a[i]; // i and j have crossed, so swap a[i] and the pivot
        a[i] = v;
        // the pivot is now in place at i; now call quicksort on the partitions
        quicksort3m(a, left, i-1); // left partition
        quicksort3m(a, i+1, right); // rightpartition.
    }
}


// hybrid sort with cutoff.
// Mainly uses quicksort.
// Insertion sort is used when array is smaller than treshold t
void hybridQuickSort(int a[], int left, int right, int t) {
    int i, j, v, temp;
    if (right - left > t) { // If partition size is greater than treshold continue with quicksort. Else use insertion sort.
        v = a[right]; // v is pivot
        i = left -1; // 1 to the left of beginning
        j = right; // 1 to the right of where search starts
        while (true) {
            while(a[++i] < v); // pre-increment i until a[i] is >= pivot
            while(a[--j] > v); // pre-decrement j until a[i] is <= pivot
            if(i >= j) break; // if i and j have crossed -- get out of loop
            temp = a[i]; // otherwise, swap a[i] and a[j]
            a[i] = a[j];
            a[j] = temp;
        }
        a[right] = a[i]; // i and j have crossed, so swap a[i] and the pivot
        a[i] = v;
        // the pivot is now in place at i; now call quicksort on the partitions
        hybridQuickSort(a, left, i-1, t); // left partition
        hybridQuickSort(a, i+1, right, t); // rightpartition.
    } else {
        insertionSort(a, left, right); // Use insertion sort for small partitions
    }
}

// Insertion sort
void insertionSort(int arr[], int low, int n) 
  {
 
    for(int i=low+1;i<n+1;i++)
    {
      int val = arr[i] ;
      int j = i ;
    while (j>low && arr[j-1]>val)
      {
        arr[j]= arr[j-1] ;
      j-= 1;
    }
    arr[j]= val ;
    } 
 
  }