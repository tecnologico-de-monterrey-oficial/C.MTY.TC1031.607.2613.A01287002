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
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> arr2 = {1, 2, 3, 4, 5, 6.7, 7, 8, 9, 10};

    std::cout << "El número 5 está en el indice " << binarySearch(arr, 5) << std::endl;
    std::cout << "El número 6.7 está en el indice " << binarySearch(arr2, 6.7) << std::endl;
    return 0;
}