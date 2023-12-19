#include "openMPMethods.h"
#include "../Utilities/utilities.h"
#include <omp.h>

void parallelMergeSort(int arr[], int l, int r, int threads);
void openMPMergeSort(int *arr, int size);
  
// l is for left index and r is 
// right index of the sub-array 
// of arr to be sorted 
void parallelMergeSort(int arr[], int l, int r, int threads) { 
    if (threads == 1) {
      mergeSort(arr, l, r);
    } else {
        if (l < r) { 
            // Same as (l+r)/2, but avoids 
            // overflow for large l and h 
            int m = l + (r - l) / 2; 
            #pragma omp parallel sections 
            {
                #pragma omp section 
                {
                    parallelMergeSort(arr, l, m, threads / 2); 
                }
                #pragma omp section 
                {
                    parallelMergeSort(arr, m + 1, r, threads / 2); 
                }
            }
            merge(arr, l, m, r);     
        }
    }
} 

void openMPMergeSort(int *arr, int size){
    int threads = omp_get_max_threads();
    omp_set_nested(1);
    parallelMergeSort(arr, 0, size - 1, threads);
}