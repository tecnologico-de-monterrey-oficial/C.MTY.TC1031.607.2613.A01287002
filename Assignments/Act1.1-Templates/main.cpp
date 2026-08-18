#include <iostream>
#include <string>
#include "list.h"

#define CONSTRUCTOR_NAME(var) std::cout << #var << std::endl

int main() {
    List<std::string> stringList;
    std::cout << "---------------------------------" << std::endl;
    CONSTRUCTOR_NAME(stringList);
    std::cout << "---------------------------------" << std::endl;
    stringList.insert("Hello");
    stringList.insert("Worldaaa");
    stringList.insert("!");
    stringList.print();
    try {
        std::cout << "Element at i = 1: " << stringList.getData(1) << std::endl;
        std::cout << "Element at i = 5: " << stringList.getData(5) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "Size: " << stringList.getSize() << std::endl;
    std::cout << "Max: " << stringList.getMax() << std::endl;

    std::cout << "---------------------------------" << std::endl;
    CONSTRUCTOR_NAME(intList);
    std::cout << "---------------------------------" << std::endl;
    List<int> intList;
    for(int i = 0; i < 5; ++i) {
        intList.insert(i);
    }
    intList.print();
    intList.removeLast();
    intList.print();
    intList.insertAt(2, 99);
    intList.print();
    intList.removeAt(1);
    intList.print();
    return 0;
}