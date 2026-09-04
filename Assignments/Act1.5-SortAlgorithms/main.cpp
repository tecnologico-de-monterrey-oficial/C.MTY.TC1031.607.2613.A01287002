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
    
    return 0;
}