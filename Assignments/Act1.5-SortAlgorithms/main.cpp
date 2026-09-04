#include "helper.h"
#include <iostream>

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    
    quickSort(arr, 0, n - 1);
    
    std::cout << "Sorted array: ";
    for(int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    std::vector<int> arr2 = {12, 11, 13, 5, 6, 7};
    mergeSort(arr2, 0, arr2.size() - 1);
    std::cout << "Sorted array mergesort: ";
    for(int i = 0; i < arr2.size(); i++)
        std::cout << arr2[i] << " ";
    std::cout << std::endl;

    return 0;
}