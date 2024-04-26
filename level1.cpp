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

int main() {
    const int size = 75000;
    int min = 0, max = 100000;
    int numbers[size] = {};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,1000000);
   

    // Inserting random numbers to array.
    for (int i = 0; i < size; i++) {
        numbers[i] = dis(gen);
    }
    cout << "First 20 numbers from unsorted array." << endl;
    for (int i = 0; i < 20; i++) {
        std::cout << numbers[i] << endl;
    }

    // Sorting array with qsort and clocking the time.
    clock_t start_time = clock();
    qsort(numbers, size, sizeof(int), compare);
    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    cout << "\n First 20 numbers from sorted array." << endl;
    for (int i = 0; i < 20; i++) {
        std::cout << numbers[i] << endl;
    }
    printf("Time spent in sorting: %f seconds\n", time_spent);

    // Writing sorted numbers to sortedNumbers.txt file
     ofstream sortedNumbers("sortedNumbers.txt");
    for (int i = 0; i < size; i++) {
        sortedNumbers << numbers[i] << "\n";
    }
    sortedNumbers.close();
    return 0;
}