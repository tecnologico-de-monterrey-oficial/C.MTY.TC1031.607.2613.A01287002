#include "heap.h"

int main() {
    Heap<int> heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);

    std::cout << "Elementos del heap: ";
    for (const auto& elem : heap.data) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    heap.remove(20);

    std::cout << "Elementos del heap después de borrar el 20: ";
    for (const auto& elem : heap.data) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}