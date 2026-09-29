#pragma once
#include <memory>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cstddef>

template <typename T>
struct Node {
    T data;
    std::unique_ptr<Node> next;

    explicit Node(T val, std::unique_ptr<Node> nextNode = nullptr)
        : data(std::move(val)), next(std::move(nextNode)) {}
};

template <typename T>
struct LinkedList {
    std::unique_ptr<Node<T>> head;

    ~LinkedList() {
        clear();
    }

    void clear() {
        while (head) {
            head = std::move(head->next);
        }
    }

    void append(T val) {
        if (!head) {
            head = std::make_unique<Node<T>>(std::move(val));
        } else {
            Node<T>* current = head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::make_unique<Node<T>>(std::move(val));
        }
    }

    void prepend(T val) {
        head = std::make_unique<Node<T>>(std::move(val), std::move(head));
    }

    void insertAt(size_t index, T val) {
        if (index == 0) {
            prepend(std::move(val));
            return;
        }

        if (!head) {
            throw std::out_of_range("Index out of bounds");
        }

        Node<T>* current = head.get();
        size_t i = 0;
            
        while (current != nullptr && i < index - 1) {
            current = current->next.get();
            i++;
        }

        if (current == nullptr) {
            throw std::out_of_range("Index out of bounds");
        }

        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(std::move(val));
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
    }

    void removeAt(size_t index) {
        if (!head) {
            throw std::out_of_range("Index out of bounds");
        }

        if (index == 0) {
            head = std::move(head->next);
            return;
        }

        Node<T>* current = head.get();
        size_t i = 0;
            
        while (current != nullptr && i < index - 1) {
            current = current->next.get();
            i++;
        }

        if (current == nullptr || !current->next) {
            throw std::out_of_range("Index out of bounds");
        }

        current->next = std::move(current->next->next);
    }

    void print() const {
        Node<T>* current = head.get();
        std::cout << "["; 
        while (current) {
            std::cout << current->data << (current->next ? ", " : "");
            current = current->next.get();
        }
        std::cout << "]" << std::endl;
    }
};