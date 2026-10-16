#pragma once 

#include <iostream>
#include <memory>
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;

    Node(int value) : data(value), next(nullptr), prev() {}
};

template <typename T>
struct SinglyLinkedList {
    std::shared_ptr<Node<int>> head;

    void push(int value) {
        auto newNode = std::make_shared<Node<int>>(value);
        newNode->next = head;
        head = newNode;
    }

    void pop() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        head = head->next;
    }

    void peek() const {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        std::cout << "Head value: " << head->data << std::endl;
    }

    bool isEmpty() const {
        return !head;
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

template <typename T>
struct DoubleLinkedList {
    std::shared_ptr<Node<int>> head;
    std::shared_ptr<Node<int>> tail;

    void push(int value) {
        auto newNode = std::make_shared<Node<int>>(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void pop() {
        if (!tail) {
            throw std::runtime_error("List is empty");
        }
        if (head == tail) {
            head.reset();
            tail.reset();
        } else {
            tail = tail->prev.lock();
            tail->next.reset();
        }
    }

    void peek() const {
        if (!tail) {
            throw std::runtime_error("List is empty");
        }
        std::cout << "Tail value: " << tail->data << std::endl;
    }

    bool isEmpty() const {
        return !head;
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