#include "Profiler.h"
#include <iostream>
#include <vector>
#include <algorithm>  // For std::sort

// Insertion sort used for small subarrays
void insertionSort(std::vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Median-of-three pivot selection
int medianOfThree(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low])
        std::swap(arr[low], arr[mid]);
    if (arr[high] < arr[low])
        std::swap(arr[low], arr[high]);
    if (arr[high] < arr[mid])
        std::swap(arr[mid], arr[high]);
    return mid;
}

// Optimized quicksort with median-of-three and insertion sort for small arrays
void quicksort(std::vector<int>& arr, int low, int high, Profiler& profiler) {
    const int threshold = 10;  // Threshold for switching to insertion sort

    while (low < high) {
        if (high - low + 1 <= threshold) {
            profiler.startSection("Insertion Sort", __FILE__, __func__, __LINE__);
            insertionSort(arr, low, high);
            profiler.endSection("Insertion Sort");
            break;
        } else {
            profiler.startSection("Partition", __FILE__, __func__, __LINE__);

            // Median-of-three pivot selection
            int pivotIndex = medianOfThree(arr, low, high);
            std::swap(arr[pivotIndex], arr[high]);  // Use the median as the pivot

            int pivot = arr[high];
            int i = (low - 1);

            for (int j = low; j <= high - 1; j++) {
                if (arr[j] < pivot) {
                    i++;
                    std::swap(arr[i], arr[j]);
                }
            }
            std::swap(arr[i + 1], arr[high]);
            profiler.endSection("Partition");

            int pi = i + 1;

            // Optimize tail recursion: recurse into the smaller half, loop over the larger
            if (pi - low < high - pi) {
                quicksort(arr, low, pi - 1, profiler);
                low = pi + 1;  // Loop for the larger half
            } else {
                quicksort(arr, pi + 1, high, profiler);
                high = pi - 1;  // Loop for the smaller half
            }
        }
    }
}

int main() {
    Profiler& profiler = Profiler::getInstance();

    // Create a large array with random values for sorting
    std::vector<int> arr = {10, 7, 8, 9, 1, 5, 3, 12, 15, 6};

    profiler.startSection("Quicksort", __FILE__, __func__, __LINE__);

    quicksort(arr, 0, arr.size() - 1, profiler);  // Run the optimized quicksort algorithm

    profiler.endSection("Quicksort");

    // Output the profiler results to CSV
    profiler.outputToFile("CSV"); 

    return 0;
}
