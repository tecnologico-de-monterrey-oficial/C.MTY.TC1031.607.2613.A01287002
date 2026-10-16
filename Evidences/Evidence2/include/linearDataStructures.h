#pragma once 

#include <iostream>
#include <memory>
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;

    Node(T value) : data(value), next(nullptr), prev() {}
};

template <typename T>
struct SinglyLinkedList {
    std::shared_ptr<Node<T>> head;

    void prepend(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        head = newNode;
    }

    void append(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!head) {
            head = newNode;
        } else {
            auto current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void removeHead() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        head = head->next;
    }

    void removeTail() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        if (!head->next) {
            head.reset();
            return;
        }
        auto current = head;
        while (current->next && current->next->next) {
            current = current->next;
        }
        current->next.reset();
    }

    size_t size() const {
        size_t count = 0;
        auto current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    void print() const {
        auto current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

template <typename T>
struct DoubleLinkedList {
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;

    void prepend(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void append(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!tail) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void placeAfter(std::shared_ptr<Node<T>> node, T value) {
        if (!node) {
            throw std::invalid_argument("Node cannot be null");
        }
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = node->next;
        newNode->prev = node;
        if (node->next) {
            node->next->prev = newNode;
        } else {
            tail = newNode;
        }
        node->next = newNode;
    }

    void removeHead() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        head = head->next;
        if (head) {
            head->prev.reset();
        } else {
            tail.reset();
        }
    }

    void removeTail() {
        if (!tail) {
            throw std::runtime_error("List is empty");
        }
        tail = tail->prev.lock();
        if (tail) {
            tail->next.reset();
        } else {
            head.reset();
        }
    }

    void removeNode(std::shared_ptr<Node<T>> node) {
        if (!node) {
            throw std::invalid_argument("Node cannot be null");
        }
        if (node == head) {
            removeHead();
            return;
        }
        if (node == tail) {
            removeTail();
            return;
        }
        auto prevNode = node->prev.lock();
        if (prevNode) {
            prevNode->next = node->next;
        }
        if (node->next) {
            node->next->prev = prevNode;
        }
    }

    void printForward() const {
        auto current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void printBackward() const {
        auto current = tail;
        while (current) {
            std::cout << current->data << " ";
            current = current->prev.lock();
        }
        std::cout << std::endl;
    }

    size_t size() const {
        size_t count = 0;
        auto current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};