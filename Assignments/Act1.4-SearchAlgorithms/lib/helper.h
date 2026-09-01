/*
#   Activity 1.4 - Search Algorithms
#   Andrés Rodríguez Cantú 
#   
#   Copyright (C) Tecnólogico de Monterrey
#   
#   File: lib/helper.h
#   
#   Created:                   25/08/2026
#   Last Modified:             25/08/2026
*/

#pragma once
#include <iostream>
#include <vector>
#include <utility>

template <typename T>
int binarySearch(const std::vector<T>& arr, T val, int p1=0, int p2= -1) {
    if (p2 == -1) {p2 = arr.size() - 1;}
    if (p1 > p2) {return -1;}
    
    int mid = p1+ (p2-p1)/2;

    if(arr.at(mid) == val) {return mid;} 
    else if(arr.at(mid) < val) {return binarySearch(arr, val, mid+1, p2);} 
    else {return binarySearch(arr, val, p1, mid-1);}
}

template <typename T>
int linearSearch(const std::vector<T>& arr, T val) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr.at(i) == val) {return i;}
    }
    return -1;
}

template <typename T>
void swapSort(std::vector<T>& arr) {
    for (size_t p1 = 0; p1 < arr.size(); p1++) {
        for (size_t p2 = p1 + 1; p2 < arr.size(); p2++) {
            if (arr[p1] > arr[p2]) {
                std::swap(arr[p1], arr[p2]);
            }
        }
    }
}

template <typename T>
void bubbleSort(std::vector<T>& arr) {
    size_t p1 = 0;
    while (p1 + 1 < arr.size()) {
        if (arr[p1] > arr[p1 + 1]) {
            std::swap(arr[p1], arr[p1 + 1]);
            p1 = 0;
        } else {
            p1++;
        }
    }
}

template <typename T>
void selectionSort(std::vector<T>& arr) {
    for(size_t i = 0; i < arr.size(); i++) {
        size_t minIdx = i;
        for(size_t j=i; j<arr.size(); j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

template <typename T>
void insertionSort(std::vector<T>& arr) {
    for(size_t i=1; i < arr.size(); i++) {
        T key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}