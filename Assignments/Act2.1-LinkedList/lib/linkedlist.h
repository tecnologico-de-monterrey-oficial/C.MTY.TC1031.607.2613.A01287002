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

    // addLast
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

    // addFirst
    void prepend(T val) {
        head = std::make_unique<Node<T>>(std::move(val), std::move(head));
    }

    // insert
    void insertAt(size_t index, T val) {
        if (index == 0) {
            prepend(std::move(val));
            return;
        }

        if (!head) {
            throw std::out_of_range("Indice fuera de rango");
        }

        Node<T>* current = head.get();
        size_t i = 0;
            
        while (current != nullptr && i < index - 1) {
            current = current->next.get();
            i++;
        }

        if (current == nullptr) {
            throw std::out_of_range("Indice fuera de rango");
        }

        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(std::move(val));
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
    }

    // deleteData
    void deleteData(const T& val) {
        if (!head) {
            throw std::out_of_range("Lista vacia");
        }

        if (head->data == val) {
            head = std::move(head->next);
            return;
        }

        Node<T>* current = head.get();
        while (current->next && current->next->data != val) {
            current = current->next.get();
        }

        if (!current->next) {
            throw std::out_of_range("Elemento no encontrado");
        }

        current->next = std::move(current->next->next);
    }

    // deleteAt
    void removeAt(size_t index) {
        if (!head) {
            throw std::out_of_range("Indice fuera de rango");
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
            throw std::out_of_range("Indice fuera de rango");
        }

        current->next = std::move(current->next->next);
    }

    // getData
    void getData(size_t index, T& val) const {
        if (!head) {
            throw std::out_of_range("Indice fuera de rango");
        }

        Node<T>* current = head.get();
        size_t i = 0;
            
        while (current != nullptr && i < index) {
            current = current->next.get();
            i++;
        }

        if (current == nullptr) {
            throw std::out_of_range("Indice fuera de rango");
        }

        val = current->data;
    }

    // updateData
    void updateData(const T& oldVal, const T& newVal) {
        if (!head) {
            throw std::out_of_range("Lista vacia");
        }

        Node<T>* current = head.get();
        while (current && current->data != oldVal) {
            current = current->next.get();
        }

        if (!current) {
            throw std::out_of_range("Elemento no encontrado");
        }

        current->data = newVal;
    }

    // updateAt
    void updateAt(size_t index, const T& newVal) {
        if (!head) {
            throw std::out_of_range("Indice fuera de rango");
        }

        Node<T>* current = head.get();
        size_t i = 0;
            
        while (current != nullptr && i < index) {
            current = current->next.get();
            i++;
        }

        if (current == nullptr) {
            throw std::out_of_range("Indice fuera de rango");
        }

        current->data = newVal;
    }

    // findData
    void findData(const T& val, size_t& index) const {
        if (!head) {
            throw std::out_of_range("Lista vacia");
        }

        Node<T>* current = head.get();
        index = 0;
        while (current && current->data != val) {
            current = current->next.get();
            index++;
        }

        if (!current) {
            throw std::out_of_range("Elemento no encontrado");
        }
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