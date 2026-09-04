#pragma once 
#include <iostream>
#include <vector>
#include <utility>

template <typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low-1;

    for(int j=low; j< high; j++) {
        if(arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i+1], arr[high]);
    return i+1;
}

template <typename T>
void quickSort(std::vector<T>& arr, int low=0, int high=-1) {
    if (low >= high) return; 
    int par = partition(arr, low, high);

    quickSort(arr, low, par - 1);
    quickSort(arr, par + 1, high); 
}