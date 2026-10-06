// Jared Aldana Palacios & Andrés Rodríguez Cantú
// A00844802 & A012870002

#pragma once
 
#include <stdexcept>
#include "Node.h"

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;
 
public:
    Queue();
    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);
    ~Queue();
 
    void push(const T& value);  
    T pop();                    
    T front() const;             
    int size() const;           
    bool isEmpty() const;       
    void clear();               
};
 
template <typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), count(0) {}
 
template <typename T>
Queue<T>::Queue(const Queue<T>& other) : head(nullptr), tail(nullptr), count(0) {
    Node<T>* current = other.head;
    while (current != nullptr) {
        push(current->data);
        current = current->next;
    }
}
 
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        clear();
        Node<T>* current = other.head;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }
    return *this;
}
 
template <typename T>
Queue<T>::~Queue() {
    clear();
}
 
template <typename T>
void Queue<T>::push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}
 
template <typename T>
T Queue<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("No se pudo borrar: el Queue esta vacio");
    }
    Node<T>* temp = head;
    T value = temp->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    count--;
    return value;
}

template <typename T>
T Queue<T>::front() const {
    if (isEmpty()) {
        throw std::out_of_range("No hay datos en el Queue");
    }
    return head->data;
}
 
template <typename T>
int Queue<T>::size() const {
    return count;
}
 
template <typename T>
bool Queue<T>::isEmpty() const {
    return head == nullptr;
}
 
template <typename T>
void Queue<T>::clear() {
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}
 