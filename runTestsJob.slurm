#!/bin/bash
#SBATCH -p classc -A  sxg125_csds438 -N 2 -n 4
#SBATCH --cpus-per-task=2
#SBATCH --mail-user=jdr161@case.edu
#SBATCH --mail-type=all

# BASELINE
module load gcc
gcc src/comparison.c src/Baseline/bubbleSort.c src/Baseline/heapSort.c src/Baseline/insertionSort.c src/Baseline/mergeSort.c src/Baseline/quickSort.c src/Baseline/radixSort.c src/OpenMP/bubbleSort.c src/OpenMP/heapSort.c src/OpenMP/insertionSort.c src/OpenMP/mergeSort.c src/OpenMP/quickSort.c src/OpenMP/radixSort.c src/Utilities/utilities.c -o comparisonRunner -fopenmp
./comparisonRunner Baseline
./comparisonRunner OpenMP
