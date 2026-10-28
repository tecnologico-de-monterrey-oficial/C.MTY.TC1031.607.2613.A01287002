#include <iostream>
#include "BST.h"


constexpr uint8_t PRE_ORDER = 0;
constexpr uint8_t IN_ORDER = 1;
constexpr uint8_t POST_ORDER = 2;
constexpr uint8_t LEVEL_ORDER = 3;

int main() {
    BST<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(51);
    
    std ::cout << "Tree structure:\n";
    tree.printTree();

    std::cout << "In-order traversal of the BST: ";
    tree.print();
    std::cout << std::endl;

    std::cout << "Searching for 40: " << (tree.search(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 100: " << (tree.search(100) ? "Found" : "Not Found") << std::endl;
    std::cout << std::endl;
    
    std::cout << "Deleting 20\n";
    tree.deleteNode(20);
    tree.printTree();
    std::cout << std::endl;
    std::cout << "Pre-order traversal of the BST: ";
    tree.visit(PRE_ORDER); 

    return 0;
}