#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class List {
public:
    List();
    ~List();

    void insert(T data);
    void removeLast();
    T getData(int index) const;
    int getSize() const;
    T getMax() const;
    void print() const;

private:
    std::vector<T> list;
    int size;
};

template <typename T>
List<T>::List() {
    size = 0;
}

template <typename T>
List<T>::~List() {}

template <typename T>
void List<T>::insert(T data) {
    list.push_back(data);
    size++;
}

template <typename T>
void List<T>::removeLast() {
    if (size > 0) {
        list.pop_back();
        size--;
    }
}

template <typename T>
T List<T>::getData(int index) const {
    if (index < 0 || index >= list.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return list.at(index);
}

template <typename T>
int List<T>::getSize() const {
    return size;
}

template <typename T>
void List<T>::print() const {
    std::cout << "List contents: " << std::endl;
    for (size_t index = 0; index < list.size(); ++index) {
        std::cout << index << " ";
        std::cout << "-" << " ";
        std::cout << list[index] << std::endl;
    }
}

template <typename T>
T List<T>::getMax() const {
    T max = list[0];
    for (const auto& item : list) {
        if (item > max) {
            max = item;
        }
    }
    return max;
}