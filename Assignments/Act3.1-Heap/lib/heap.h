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

    int child(int index, bool left) {
        return left ? 2 * index + 1 : 2 * index + 2;
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

    void heapifyDown(int index) {
        int leftChild = child(index, true);
        int rightChild = child(index, false);
        int largest = index;

        if (leftChild < data.size() && data[leftChild] > data[largest]) {
            largest = leftChild;
        }
        if (rightChild < data.size() && data[rightChild] > data[largest]) {
            largest = rightChild;
        }
        if (largest != index) {
            std::swap(data[index], data[largest]);
            heapifyDown(largest);
        }
    }

    void insert(const T& value) {
        // Insertamos usando pushback 
        data.push_back(value);
        // Actualizamos la posición del elemento 
        heapifyUp(data.size() - 1);
    }

    void remove(const T& value) {
        // Buscamos el valor en el heap
        int index = -1;
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] == value) {
                index = i;
                break;
            }
        }

        // Si no encontramos el valor, retornamos
        if (index == -1) {
            return;
        }

        // Reemplazamos el valor a eliminar con el último elemento
        data[index] = data.back();
        data.pop_back();

        // Reajustamos el heap
        heapifyDown(index);
    }

    void buildHeap(const std::vector<T>& values) {
        data = values;
        for (int i = parent(data.size() - 1); i >= 0; --i) {
            heapifyDown(i);
        }
    }
};