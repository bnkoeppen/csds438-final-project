#include <stdio.h>
#include "../Utilities/utilities.h"

void pQuickSort(int arr[], int low, int high)
{
    if(low<high)
    {
        int piv = partition(arr, low, high);
        
        #pragma omp task
        {
            pQuickSort(arr, low, piv-1);
        }
        pQuickSort(arr, piv+1, high);
    }
}

void openMPQuickSort(int *arr, int size){
    pQuickSort(arr, 0, size - 1);
}