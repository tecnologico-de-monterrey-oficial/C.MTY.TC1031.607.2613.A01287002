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
    Node* prev;

    explicit Node(T val, std::unique_ptr<Node> nextNode = nullptr, Node* prevNode = nullptr)
        : data(std::move(val)), next(std::move(nextNode)), prev(prevNode) {}
};

template <typename T>
struct DoubleLinkedList {
    std::unique_ptr<Node<T>> head;
    Node<T>* tail = nullptr;

    DoubleLinkedList() = default;

    DoubleLinkedList(const DoubleLinkedList& other) {
        for (Node<T>* src = other.head.get(); src != nullptr; src = src->next.get()) {
            addLast(src->data);
        }
    }

    DoubleLinkedList(DoubleLinkedList&& other) noexcept
        : head(std::move(other.head)), tail(other.tail) {
        other.tail = nullptr;
    }

    DoubleLinkedList& operator=(DoubleLinkedList&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        clear();
        head = std::move(other.head);
        tail = other.tail;
        other.tail = nullptr;

        return *this;
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& other) {
        if (this == &other) {
            return *this;
        }

        clear();

        for (Node<T>* src = other.head.get(); src != nullptr; src = src->next.get()) {
            addLast(src->data);
        }

        return *this;
    }

    T& operator[](size_t index) {
        return nodeAt(index)->data;
    }

    const T& operator[](size_t index) const {
        return nodeAt(index)->data;
    }

    ~DoubleLinkedList() {
        clear();
    }

    size_t size() const {
        size_t count = 0;
        for (Node<T>* current = head.get(); current != nullptr; current = current->next.get()) {
            count++;
        }
        return count;
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        while (head) {
            head = std::move(head->next);
        }
        tail = nullptr;
    }

    void addFirst(T val) {
        head = std::make_unique<Node<T>>(std::move(val), std::move(head));
        if (head->next) {
            head->next->prev = head.get();
        } else {
            tail = head.get();
        }
    }

    void addLast(T val) {
        if (!head) {
            head = std::make_unique<Node<T>>(std::move(val));
            tail = head.get();
        } else {
            tail->next = std::make_unique<Node<T>>(std::move(val), nullptr, tail);
            tail = tail->next.get();
        }
    }

    void insert(size_t index, T val) {
        Node<T>* current = nodeAt(index);

        if (current == tail) {
            addLast(std::move(val));
            return;
        }

        std::unique_ptr<Node<T>> newNode =
            std::make_unique<Node<T>>(std::move(val), std::move(current->next), current);
        newNode->next->prev = newNode.get();
        current->next = std::move(newNode);
    }

    bool deleteData(const T& val) {
        Node<T>* current = head.get();
        while (current && current->data != val) {
            current = current->next.get();
        }

        if (!current) {
            return false;
        }

        unlink(current);
        return true;
    }

    bool deleteAt(size_t index) {
        Node<T>* current = head.get();
        size_t i = 0;

        while (current != nullptr && i < index) {
            current = current->next.get();
            i++;
        }

        if (current == nullptr) {
            return false;
        }

        unlink(current);
        return true;
    }

    T getData(size_t index) const {
        return nodeAt(index)->data;
    }

    void updateData(const T& oldVal, const T& newVal) {
        Node<T>* current = head.get();
        while (current && current->data != oldVal) {
            current = current->next.get();
        }

        if (!current) {
            throw std::out_of_range("Elemento no encontrado");
        }

        current->data = newVal;
    }

    void updateAt(size_t index, const T& newVal) {
        nodeAt(index)->data = newVal;
    }

    int findData(const T& val) const {
        Node<T>* current = head.get();
        int index = 0;

        while (current) {
            if (current->data == val) {
                return index;
            }
            current = current->next.get();
            index++;
        }

        return -1;
    }

    void sort() {
        if (!head || !head->next) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node<T>* current = head.get();

            while (current->next) {
                if (current->data > current->next->data) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next.get();
            }
        } while (swapped);
    }

    void duplicate() {
        Node<T>* current = head.get();

        while (current) {
            std::unique_ptr<Node<T>> newNode =
                std::make_unique<Node<T>>(current->data, std::move(current->next), current);
            if (newNode->next) {
                newNode->next->prev = newNode.get();
            } else {
                tail = newNode.get();
            }
            current->next = std::move(newNode);
            current = current->next->next.get();
        }
    }

    void removeDuplicates() {
        Node<T>* current = head.get();

        while (current) {
            Node<T>* runner = current->next.get();
            while (runner) {
                Node<T>* nextRunner = runner->next.get();
                if (runner->data == current->data) {
                    unlink(runner);
                }
                runner = nextRunner;
            }
            current = current->next.get();
        }
    }

    void print() const {
        Node<T>* current = head.get();
        std::cout << "[";
        while (current) {
            std::cout << current->data << (current->next ? " <-> " : "");
            current = current->next.get();
        }
        std::cout << "]" << std::endl;
    }

    void printReverse() const {
        Node<T>* current = tail;
        std::cout << "[";
        while (current) {
            std::cout << current->data << (current->prev ? " <-> " : "");
            current = current->prev;
        }
        std::cout << "]" << std::endl;
    }

private:
    Node<T>* nodeAt(size_t index) const {
        Node<T>* current = head.get();
        size_t i = 0;

        while (current != nullptr && i < index) {
            current = current->next.get();
            i++;
        }

        if (current == nullptr) {
            throw std::out_of_range("Indice fuera de rango");
        }

        return current;
    }

    void unlink(Node<T>* node) {
        Node<T>* before = node->prev;

        if (node->next) {
            node->next->prev = before;
        } else {
            tail = before;
        }

        if (before) {
            before->next = std::move(node->next);
        } else {
            head = std::move(node->next);
        }
    }
};
