#pragma once
#include <memory>
#include <iostream>
#include <utility>

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

    void append(T val) {
        if (!head) {
            head = std::make_unique<Node<T>>(val);
        } else {
            Node<T>* current = head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::make_unique<Node<T>>(val);
        }
    }

    void prepend(T val) {
        head = std::make_unique<Node<T>>(val, std::move(head));
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