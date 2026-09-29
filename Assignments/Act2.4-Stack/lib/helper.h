#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstddef>

#include "linkedlist.h"

template <typename T>
struct Stack {
    LinkedList<T> list;

    void push(T val) {
        list.prepend(std::move(val));
    }

    void pop() {
        if (!list.head) {
            throw std::out_of_range("Stack esta vacio");
        }
        list.removeAt(0);
    }

    const T& top() const {
        if (!list.head) {
            throw std::out_of_range("Stack esta vacio");
        }
        return list.head->data;
    }

    void print() const {
        list.print();
    }

    size_t size() const {
        size_t count = 0;
        Node<T>* current = list.head.get();
        while (current) {
            count++;
            current = current->next.get();
        }
        return count;
    }
};