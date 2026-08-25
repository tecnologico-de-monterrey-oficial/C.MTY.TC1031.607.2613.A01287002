/*
#   Activity 1.3 - Big O Notation
#   Andrés Rodríguez Cantú 
#   
#   Copyright (C) Tecnólogico de Monterrey
#   
#   File: lib/helper.h
#   
#   Created:                   24/08/2026
#   Last Modified:             24/08/2026
*/

#pragma once
#include <iostream>
#include <vector>

// O(n)
int oddPairSumIter(const std::vector<int>& arr) {
    int sum = 0;
    for(size_t i = 0; i < arr.size(); i += 2) {
        sum += arr[i];
    }
    return sum;
}

// O(n)
int oddPairSumRec(const std::vector<int>& arr, size_t idx = 0) {
    if(idx >= arr.size()) return 0;
    return arr[idx] + oddPairSumRec(arr, idx + 2);
}
