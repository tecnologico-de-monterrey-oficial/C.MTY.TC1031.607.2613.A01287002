#pragma once
#include <cstdint>
#include <iostream>
#include <memory>
#include <queue>

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

    // De https://www.geeksforgeeks.org/dsa/deletion-in-binary-search-tree/
    // Helper functions
    Node<T>* findMin(Node<T>* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }

    Node<T>* findMax(Node<T>* node) const {
        while (node && node->right) {
            node = node->right.get();
        }
        return node;
    }
    
    void deleteNode(T val) {
        root = deleteHelper(std::move(root), val);
    }

    std::unique_ptr<Node<T>> deleteHelper(std::unique_ptr<Node<T>> node, T val) {
        if (!node) {
            return nullptr;
        }
        if (val < node->data) {
            node->left = deleteHelper(std::move(node->left), val);
        } else if (val > node->data) {
            node->right = deleteHelper(std::move(node->right), val);
        } else {
            if (!node->left) {
                return std::move(node->right);
            } else if (!node->right) {
                return std::move(node->left);
            } else {
                Node<T>* minNode = findMin(node->right.get());
                node->data = minNode->data;
                node->right = deleteHelper(std::move(node->right), minNode->data);
            }
        }
        return node;
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

    // Print realizado con Gemini
    void printTree() const {
        if (root) {
            printTreeHelper(root, "", false, true);
        }
    }

    void printTreeHelper(const std::unique_ptr<Node<T>>& node, 
                        const std::string& prefix, 
                        bool isLeft, 
                        bool isRoot = false) const {
        if (!node) {
            return;
        }

        if (node->right) {
            printTreeHelper(node->right, 
                            prefix + (isRoot ? "" : (isLeft ? "│   " : "    ")), 
                            false, 
                            false);
        }

        std::cout << prefix;
        if (!isRoot) {
            std::cout << (isLeft ? "└── " : "┌── ");
        }
        std::cout << node->data << "\n";

        if (node->left) {
            printTreeHelper(node->left, 
                            prefix + (isRoot ? "" : (isLeft ? "    " : "│   ")), 
                            true, 
                            false);
        }
    }

    // Regresa un valor booleano, si es que encontró el dato buscado en el BST.
    // Valor booleano que indica si el dato se encontraba en el BST.
    // Sin usar search, se debe de recorrer el árbol para encontrar el dato.
    bool findNode(T val) const {
        return searchHelper(root, val);
    }

    // Encuentra el nodo con el valor mínimo en un subárbol dado.
    std::unique_ptr<Node<T>> searchHelper(Node<T>* node, T val) const {
        if (!node) {
            return nullptr;
        }
        if (node->data == val) {
            return node;
        }
        if (val < node->data) {
            return searchHelper(node->left.get(), val);
        } else {
            return searchHelper(node->right.get(), val);
        }
    }

    void visit(uint8_t mode) const {
        visitHelper(root.get(), mode);
    }

    int visitHelper(Node<T>* node, uint8_t mode) const {
        switch (mode) {
            case 0: { // Pre-order
                if (!node) {
                    return 0;
                }
                std::cout << node->data << " ";
                return 1 + visitHelper(node->left.get(), mode) + visitHelper(node->right.get(), mode);
            }
            case 1: { // In-order
                if (!node) {
                    return 0;
                }
                int count = visitHelper(node->left.get(), mode);
                std::cout << node->data << " ";
                count += 1 + visitHelper(node->right.get(), mode);
                return count;
            }
            case 2: { // Post-order
                if (!node) {
                    return 0;
                }
                int postCount = visitHelper(node->left.get(), mode);
                postCount += visitHelper(node->right.get(), mode);
                std::cout << node->data << " ";
                return postCount + 1;
            }
            case 3: { // Level-order
                if (!node) {
                    return 0;
                }
                std::queue<Node<T>*> q;
                q.push(node);
                int levelCount = 0;
                while (!q.empty()) {
                    Node<T>* current = q.front();
                    q.pop();
                    std::cout << current->data << " ";
                    levelCount++;
                    if (current->left) {
                        q.push(current->left.get());
                    }
                    if (current->right) {
                        q.push(current->right.get());
                    }
                }
                return levelCount;
            }
            default:
                return 0;
        }
    }
};