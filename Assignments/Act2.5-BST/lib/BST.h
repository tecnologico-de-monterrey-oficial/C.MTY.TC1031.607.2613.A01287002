#pragma once
#include <memory>
#include <iostream>

template <class T>
struct Node {
    T data;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;

    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
struct BST {
    std::unique_ptr<Node<T>> root;

    BST() : root(nullptr) {}

    void insert(T val) {
        if (!root) {
            root = std::make_unique<Node<T>>(val);
        } else {
            insertHelper(root, val);
        }
    }

    void insertHelper(std::unique_ptr<Node<T>>& node, T val) {
        if (val < node->data) {
            if (!node->left) {
                node->left = std::make_unique<Node<T>>(val);
            } else {
                insertHelper(node->left, val);
            }
        } else {
            if (!node->right) {
                node->right = std::make_unique<Node<T>>(val);
            } else {
                insertHelper(node->right, val);
            }
        }
    }

    bool search(T val) const {
        return searchHelper(root, val);
    }

    bool searchHelper(const std::unique_ptr<Node<T>>& node, T val) const {
        if (!node) {
            return false;
        }
        if (node->data == val) {
            return true;
        }
        if (val < node->data) {
            return searchHelper(node->left, val);
        } else {
            return searchHelper(node->right, val);
        }
    }

    // Print
    void print() const {
        printHelper(root);
    }
    
    void printHelper(const std::unique_ptr<Node<T>>& node) const {
        if (node) {
            printHelper(node->left);
            std::cout << node->data << " ";
            printHelper(node->right);
        }
    }
};