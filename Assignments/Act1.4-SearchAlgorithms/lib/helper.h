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

template <typename T>
int binarySearch(const std::vector<T>& arr, T val, int p1=0, int p2= -1) {
    if (p2 == -1) {p2 = arr.size() - 1;}
    if (p1 > p2) {return -1;}
    
    int mid = p1+ (p2-p1)/2;

    if(arr.at(mid) == val) {return mid;} 
    else if(arr.at(mid) < val) {return binarySearch(arr, val, mid+1, p2);} 
    else {return binarySearch(arr, val, p1, mid-1);}
}
