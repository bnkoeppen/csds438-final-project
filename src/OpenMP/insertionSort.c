#include <omp.h>
#include <string.h>
#include "../Baseline/baselineMethods.h"
#include "../Utilities/utilities.h"

void openMPInsertionSort(int *arr, int size){
    int threads = omp_get_max_threads();
    int rem = size % threads;
    int part = size/threads;
    int subarraysizes[threads];
    int subarrayoffsets[threads];

    for(int i = 0; i < threads; i++) {
        subarraysizes[i] = part;
        subarrayoffsets[i] = 0;
    }

    for (int i = 0; i < rem; i++){
        subarraysizes[i]++;
    }

    for (int i = 1; i < threads; i++){
        subarrayoffsets[i] = subarrayoffsets[i-1] + subarraysizes[i-1];
    }

    #pragma omp parallel
    {
        int t = omp_get_thread_num();
        baselineInsertionSort(arr + subarrayoffsets[t], subarraysizes[t]);
    }

    for (int i = 1; i < threads; i++){
        merge(arr, 0, subarrayoffsets[i] - 1, subarrayoffsets[i] + subarraysizes[i] - 1);
    }
}