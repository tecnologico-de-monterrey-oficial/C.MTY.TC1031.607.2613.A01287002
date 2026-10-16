#include "BST.h"

int main() {
    BST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "In-order traversal of the BST: ";
    tree.print();
    std::cout << std::endl;

    return 0;
}