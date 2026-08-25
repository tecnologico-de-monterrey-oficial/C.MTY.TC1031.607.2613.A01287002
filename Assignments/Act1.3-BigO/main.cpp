/*
#   Activity 1.3 - Big O Notation
#   Andrés Rodríguez Cantú 
#   
#   Copyright (C) Tecnólogico de Monterrey
#   
#   File: main.cpp
#   
#   Created:                   24/08/2026
#   Last Modified:             24/08/2026
*/

#include "helper.h"

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "Suma de elementos en posiciones impares (Iterativa): " << oddPairSumIter(arr) << std::endl;
    std::cout << "Suma de elementos en posiciones impares (Recursiva): " << oddPairSumRec(arr) << std::endl;
    return 0;
}