#include "openMPMethods.h"
#include "../Utilities/utilities.h"
#include <omp.h>
#include "../Baseline/baselineMethods.h"

void openMPHeapSort(int *arr, int size){
    baselineHeapSort(arr, size);
}