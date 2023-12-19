#include <stdio.h>

void baselineBubbleSort(int *arr, int size) { 
    int iteration = 0;
    int pos = 0;

    for (iteration = 0; iteration < size - 1; iteration++) {
        for (pos = 0; pos < size - iteration -1 ; pos ++) {
            if (arr[pos] > arr[pos + 1]) {
                int temp = arr[pos];
                arr[pos] = arr[pos + 1];
                arr[pos + 1] = temp;
                
            }
        }
    }
}

