#pragma once
#include <memory>
#include <iostream>
#include <vector>

template <typename T>
struct Heap {
    std::vector<T> data;

    int parent(int index) {
        return (index - 1) / 2;
    }

    void heapifyUp(int index) {
        // Mientras que i > 0, entonces el padre de i es mayor que i.
        // Aqui swappeamos padre e hijo
        while (index > 0 && data[index] > data[parent(index)]) {
            std::swap(data[index], data[parent(index)]);
            // Actualizamos el index al padre
            index = parent(index); 
        }
    }

    void insert(const T& value) {
        // Insertamos usando pushback 
        data.push_back(value);
        // Actualizamos la posición del elemento 
        heapifyUp(data.size() - 1);
    }
};