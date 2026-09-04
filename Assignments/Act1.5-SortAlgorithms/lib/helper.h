#pragma once 
#include <iostream>
#include <vector>
#include <utility>

// --- Quicksort ---

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

// --- mergesort ---

template <typename T>
void merge(std::vector<T>& arr, int low, int mid, int high) {
    std::vector<T> tmp;
    tmp.reserve(high-low+1);

    for(int i=low; i<= mid; i++) {
        tmp.push_back(arr[i]);
    }
    for(int i=mid+1; i<= high; i++) {
        tmp.push_back(arr[i]);
    }

    int i = 0, j = mid - low + 1;
    for(int k=low; k<= high; k++) {
        if(i < mid - low + 1 && j < high - low + 1) {
            if(tmp[i] < tmp[j]) {
                arr[k] = tmp[i];
                i++;
            } else {
                arr[k] = tmp[j];
                j++;
            }
        } else if(i < mid - low + 1) {
            arr[k] = tmp[i];
            i++;
        } else {
            arr[k] = tmp[j];
            j++;
        }
    }
}

template <typename T>
void mergeSort(std::vector<T>& arr, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;

    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}