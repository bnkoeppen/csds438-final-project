#include "openMPMethods.h"
#include "../Utilities/utilities.h"
#include "../Baseline/baselineMethods.h"
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void parallelRadixSort(int *arr, int size) {

    int *sorted = malloc(sizeof(int) * size);

    for(int place = 0; place < 8; place++) {
        int count[16] = {0};
        int offset[16] = {0};

        #pragma omp parallel
        {
            int localcount[16] = {0};
            int localoffset[16] = {0};

            // Each thread does its own bit of counting, no rejoin
            #pragma omp for schedule(static) nowait
            for(int i = 0; i < size; i++) {
                int digit = nthNibble(arr[i], place);
                localcount[digit]++;
            }

            // Counts are summed, critical to prevent race condition
            #pragma omp critical
            for(int i = 0; i < 16; i++) {
                count[i] += localcount[i];
            }
            
            #pragma omp barrier // rejoin

            // One thread creates the global offsets
            #pragma omp single
            {
                offset[0] = 0;
                for(int i = 1; i < 16; i++) {
                    offset[i] = offset[i - 1] + count[i - 1];
                }
            }

            int threads = omp_get_max_threads();
            int tid = omp_get_thread_num();
            
            // Threads wait for each other to make their own offsets
            for(int currthread = 0; currthread < threads; currthread++) {
                if(tid == currthread) {
                    for(int i = 0; i < 16; i++) {
                        localoffset[i] = offset[i];
                        offset[i] += localcount[i];
                    }
                }
                #pragma omp barrier
            }

            // Placed into final array
            #pragma omp for schedule(static)
            for(int i = 0; i < size; i++) {
                int digit = nthNibble(arr[i], place);
                sorted[localoffset[digit]] = arr[i];
                localoffset[digit]++;
            }
        }
        
        int *temp = arr;
        arr = sorted;
        sorted = temp;

    }
}

void parallelSignFlip(int *arr, int size) {
    const int MASK = 0x80000000; // 1 at sign bit 0 at all other bits
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < size; i++) {
        arr[i] = arr[i] ^ MASK;
    }
}

void openMPRadixSort(int *arr, int size){
    int threads = omp_get_max_threads();
    omp_set_nested(1);
    
    if(threads == 1) {
        baselineRadixSort(arr, size);
    }
    else {
        parallelSignFlip(arr, size);
        parallelRadixSort(arr, size);
        parallelSignFlip(arr, size);
    }
}