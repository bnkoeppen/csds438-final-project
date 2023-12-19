#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "baselineMethods.h"
#include "../Utilities/utilities.h"

// Base 16 radix sort so it can be done with bitwise comparisons instead of expensive modulus operations

void baselineRadixSort(int *arr, int size){

    signFlip(arr, size); // This way when you do bit comparisons it sorts properly
    
    int *sorted = malloc(sizeof(int) * size);
    for(int place = 0; place < 8; place++) {
        int count[16] = {0};
        int offset[16];
    

        // Count number of entries with each digit
        for(int i = 0; i < size; i++) {
            int digit = nthNibble(arr[i], place);
            count[digit]++;
        }

        // Assign starting positions in bucket for output
        offset[0] = 0;
        for(int i = 1; i < 16; i++) {
            offset[i] = offset[i - 1] + count[i - 1];
        }

        // Fill buckets
        for(int i = 0; i < size; i++) {
            int digit = nthNibble(arr[i], place);
            sorted[offset[digit]] = arr[i];
            offset[digit]++;
        }
        int *temp = arr;
        arr = sorted;
        sorted = temp;

    }

    signFlip(arr, size);

}