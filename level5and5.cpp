#include <iostream>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

// Compare function for qsort algorithm.
int compare(const void *a, const void *b) {

    int int_a = *((int*)a);
    int int_b = *((int*)b);

    if (int_a < int_b) {
        return -1;
    } else if (int_a > int_b) {
        return 1;
    } else {
        return 0;
    }
}

// Quicksort algorithm with median of 3.
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

// hybrid sort with cutoff.
// Mainly uses quicksort.
// Insertion sort is used when array is smaller than threshold t
void hybridQuickSort(int a[], int left, int right, int t) {
    int i, j, v, temp;
    if (right - left > t) { // If partition size is greater than threshold continue with quicksort. Else use insertion sort.
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


int main() {
    // Setting up array with random numbers.
    const int size = 75000;
    int min = 0, max = 100000;
    int randomNumbers[size] = {};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,1000000);
    // Inserting random numbers to array.
    for (int i = 0; i < size; i++) {
        randomNumbers[i] = dis(gen);
    }

    // cout << "First 20 numbers from unsorted array." << endl;
    // for (int i = 0; i < 20; i++) {
    //     std::cout << randomNumbers[i] << endl;
    // }

    // Copying the random array for: qsort, quicksort with median of three and quicksort with cutoffs.
    int qsortNumbers[size] = {};
    int quickSort3Numbers[size] = {};
    for (int i = 0; i < size; ++i) {
        qsortNumbers[i] = randomNumbers[i];
        quickSort3Numbers[i] = randomNumbers[i];
    }

    // 1. Sorting array with qsort and clocking the time.
    clock_t qsort_start_time = clock();
    qsort(qsortNumbers, size, sizeof(int), compare);
    clock_t qsort_end_time = clock();
    double qsort_time_spent = (double)(qsort_end_time - qsort_start_time) / CLOCKS_PER_SEC;
    printf("Time spent with qsort: %f seconds\n", qsort_time_spent);


    // 2. Sorting array with quicksort with median of three and clocking the time.
    clock_t quicks3m_start_time = clock();
    quicksort3m(quickSort3Numbers, 0, size-1);
    clock_t quicks3m_end_time = clock();
    double quicks3m_time_spent = (double)(quicks3m_end_time - quicks3m_start_time) / CLOCKS_PER_SEC;
    printf("Time spent with quicksort with median of 3: %f seconds\n", quicks3m_time_spent);


    

    // 3. Sorting array with hybrid quicksort with cutoff (<t)
    const int tresholdMax = 50;
    double fastestTime = 1.0;
    int optimumTreshold;
    int hybridQuickSortNumbers[size] = {}; // Creating a multidimensional array that contains own array of random values for each cutoff threshold number.
    
    for(int t = 0; t < tresholdMax; ++t) { // Iterates through all threshold values.
        for (int i = 0; i < size; ++i) { // Fills the thresholds array with the pre defined random values.
            hybridQuickSortNumbers[i] = randomNumbers[i];
        }
        // Sorts thresholds array with hybrid quicksort and clocks the time.
        clock_t hybridS_start_time = clock();
        hybridQuickSort(hybridQuickSortNumbers, 0, size-1, t);
        clock_t hybridS_end_time = clock();
        double hybridS_time_spent = (double)(hybridS_end_time - hybridS_start_time) / CLOCKS_PER_SEC;
        if (fastestTime > hybridS_time_spent) { // if we get new fastest time save it.
            fastestTime = hybridS_time_spent;
            optimumTreshold = t;
        }
    }
    printf("Time spent with quicksort with cutoff: %f seconds and optimum cutoff treshold: %i\n", fastestTime, optimumTreshold);
    
    return 0;
}