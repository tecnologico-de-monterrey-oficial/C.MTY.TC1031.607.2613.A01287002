/*
#   Activity 1.4 - Search Algorithms
#   Andrés Rodríguez Cantú 
#   
#   Copyright (C) Tecnólogico de Monterrey
#   
#   File: main.cpp
#   
#   Created:                   25/08/2026
#   Last Modified:             25/08/2026
*/

#include "helper.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> arr = {5, 2, 1, 4, 3};
    std::vector<int> arr2 = {3, 45, 12, 54, 13, 66, 2};

    bubbleSort(arr2);
    std::cout << "Array: ";
    for (const auto& val : arr2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // std::cout << "El número 5 está en el indice " << binarySearch(arr, 5) << std::endl;
    // std::cout << "El número 6.7 está en el indice " << binarySearch(arr2, 6.7) << std::endl;
    return 0;
}