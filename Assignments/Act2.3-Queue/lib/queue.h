#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstddef>

#include "linkedlist.h"

template <typename T>
struct Queue {
    LinkedList<T> list;

    void push(T val) {
        list.append(std::move(val));
    }

    void pop() {
        if (!list.head) {
            throw std::out_of_range("Queue is empty");
        }
        list.removeAt(0);
    }

    // Access front element (modifiable)
    T& front() {
        if (!list.head) {
            throw std::out_of_range("Queue is empty");
        }
        return list.head->data;
    }

    // Access front element (read-only)
    const T& front() const {
        if (!list.head) {
            throw std::out_of_range("Queue is empty");
        }
        return list.head->data;
    }

    // Access back element (modifiable)
    T& back() {
        if (!list.head) {
            throw std::out_of_range("Queue is empty");
        }
        Node<T>* current = list.head.get();
        while (current->next) {
            current = current->next.get();
        }
        return current->data;
    }

    // Access back element (read-only)
    const T& back() const {
        if (!list.head) {
            throw std::out_of_range("Queue is empty");
        }
        Node<T>* current = list.head.get();
        while (current->next) {
            current = current->next.get();
        }
        return current->data;
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

    bool isEmpty() const {
        return !list.head;
    }

    void print() const {
        list.print();
    }
};