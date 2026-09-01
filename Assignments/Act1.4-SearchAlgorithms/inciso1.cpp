#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "helper.h"

int main() {
    std::vector<int> arr(10000);
    for (int i = 0; i < 10000; i++) {
        arr[i] = rand() % 1000000 + 1;
    }

    std::sort(arr.begin(), arr.end());

    int num;
    std::cout << "Ingrese un número entero entre 1 y 1,000,000: ";
    std::cin >> num;

    auto start = std::chrono::high_resolution_clock::now();
    int index = binarySearch(arr, num);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> binaryDuration = end - start;

    if (index != -1) {
        std::cout << "El número " << num << " se encuentra en el índice " << index << "." << std::endl;
    } else {
        std::cout << "El número " << num << " no se encuentra en la lista." << std::endl;
    }
    std::cout << "Tiempo de búsqueda binaria: " << binaryDuration.count() << " segundos." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    index = linearSearch(arr, num);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> linearDuration = end - start;

    if (index != -1) {
        std::cout << "El número " << num << " se encuentra en el índice " << index << "." << std::endl;
    } else {
        std::cout << "El número " << num << " no se encuentra en la lista." << std::endl;
    }
    std::cout << "Tiempo de búsqueda secuencial: " << linearDuration.count() << " segundos." << std::endl;
}