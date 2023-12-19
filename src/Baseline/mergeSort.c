#include "baselineMethods.h"
#include "../Utilities/utilities.h"
#include <stdio.h>

void baselineMergeSort(int *arr, int size){
    mergeSort(arr, 0, size - 1);
}