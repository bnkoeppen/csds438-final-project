#include <stdio.h>
#include "../Utilities/utilities.h"

void quickSort(int arr[], int low, int high)
{
    if(low<high)
    {
        int piv = partition(arr, low, high);
        quickSort(arr, low, piv-1);
        quickSort(arr, piv+1, high);
    }
}
void baselineQuickSort(int *arr, int size){
    quickSort(arr, 0, size - 1);
}