/**
 * This is the file where we will call each of the sorting algorithms and time how long it takes for them to run
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "Baseline/baselineMethods.h"
#include "OpenMP/openMPMethods.h"

// so we can have an array of pointers to sorting algorithms
typedef void (*func)(int *, int);
int* arrayCopy(int arr[], int copy[], int size);
int main (int argc, char *argv[]);

int* arrayCopy(int arr[], int copy[], int size){
    for(int i = 0; i < size; i++){
        copy[i] = arr[i];
    }
    return copy;
}

void loadData(int *arr1, int *arr2, int *arr3, int *arr4) {
    FILE *data1 = fopen("./data/dataset-1", "rb");
    if(data1 == NULL) {printf("data1 failed to open"); exit(-1);}

    FILE *data2 = fopen("./data/dataset2", "rb");
    if(data2 == NULL) {printf("data2 failed to open"); exit(-1);}

    FILE *data3 = fopen("./data/dataset3", "rb");
    if(data3 == NULL) {printf("data3 failed to open"); exit(-1);}

    FILE *data4 = fopen("./data/dataset4", "rb");
    if(data4 == NULL) {printf("data4 failed to open"); exit(-1);}


    fread(arr1, 4, 2000000, data1);
    fread(arr2, 4, 2000000, data2);
    fread(arr3, 4, 2000000, data3);
    fread(arr4, 4, 2000000, data4);
}

int main(int argc, char *argv[]){
    if(argc == 1){
        printf("Missing argument: programming model. Example: \"./comparison Baseline\"");
        exit(-1);
    } else if(argc > 2){
        printf("Too many arguments provided. Expected 1 arguments, given %d", argc - 1);
        exit(-1);
    }
    
    int* datasets[4];
    for(int i = 0; i < 4; i++) {
        datasets[i] = (int *)malloc(2000000*sizeof(int));
    }

    func sortingAlgorithms[6];
    char *algoNames[] = {"Bubble Sort", "Heap Sort", "Insertion Sort", "Merge Sort", "Quick Sort", "Radix Sort"};
    char *progMethod;
    clock_t start, end;
    double totalTime;

    if(strcmp(argv[1], "Baseline") == 0){
        sortingAlgorithms[0] = &baselineBubbleSort;
        sortingAlgorithms[1] = &baselineHeapSort;
        sortingAlgorithms[2] = &baselineInsertionSort;
        sortingAlgorithms[3] = &baselineMergeSort; 
        sortingAlgorithms[4] = &baselineQuickSort;
        sortingAlgorithms[5] = &baselineRadixSort;
        progMethod = "Baseline";
    } else if(strcmp(argv[1], "OpenMP") == 0){
        sortingAlgorithms[0] = &openMPBubbleSort;
        sortingAlgorithms[1] = &openMPHeapSort;
        sortingAlgorithms[2] = &openMPInsertionSort;
        sortingAlgorithms[3] = &openMPMergeSort; 
        sortingAlgorithms[4] = &openMPQuickSort;
        sortingAlgorithms[5] = &openMPRadixSort;
        progMethod = "OpenMP";
    } else {
        printf("Unrecognized programming model \"%s\"", argv[1]);
        exit(-1);
    }

    loadData(datasets[0], datasets[1], datasets[2], datasets[3]);

    int sizes[9] = {1000, 2000, 5000, 10000, 50000, 100000, 200000, 1000000, 2000000};

    for(int size_index = 0; size_index < 9; size_index++) {
        int size = sizes[size_index];

        for(int dataset_index = 0; dataset_index < 4; dataset_index++) {
            int *dataset = datasets[dataset_index];

            for(int i = 0; i < 6; i++){       
                if(strcmp(argv[1], "OpenMP") == 0 && i == 1) {continue;} //skip heapsort in openmp

                func sort = sortingAlgorithms[i];
                int *copyToSort = (int *)malloc(size * sizeof(int));
                arrayCopy(dataset, copyToSort, size);
                
                start = clock();
                sort(copyToSort, size);
                end = clock();

                // Confirm list is sorted
                bool isSorted = true;
                for(int j = 0; j < size - 1; j++){
                    if(copyToSort[j] > copyToSort[j+1]){
                        isSorted = false;
                    }
                }
                if(!isSorted){
                    printf("LIST NOT SORTED, BRUH: %s", algoNames[i]);
                }
                free(copyToSort);

                totalTime = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("size=%d, dataset#=%d, method=%s, algorithm=%s, time=%.4fs\n", size, dataset_index + 1, progMethod, algoNames[i], totalTime);
            }
        }
    }
}