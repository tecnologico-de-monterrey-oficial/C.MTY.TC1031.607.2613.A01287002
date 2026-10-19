#include "linearDataStructures.h"
#include <iostream>

int main() {
    SinglyLinkedList<int> list;
    std::cout << "--- Single Linked List Test ---" << std::endl;
    list.append(1);
    list.append(2);
    list.append(3);
    list.prepend(0);
    std::cout << "List size: " << list.size() << std::endl;
    list.print();
    std::cout << "Removing head..." << std::endl;
    list.removeHead();
    list.print();
    std::cout << "Removing tail..." << std::endl;
    list.removeTail();
    list.print();

    std::cout << "--- Double Linked List Test ---" << std::endl;
    DoubleLinkedList<int> dlist;
    dlist.append(1);
    dlist.append(2);
    dlist.append(3);
    dlist.placeAfter(dlist.head, 1);
    dlist.prepend(0); std::cout << std::endl;
    std::cout << "Double Linked List size: " << dlist.size() << std::endl;
    std::cout << "Printing forward: ";
    dlist.printForward();
    std::cout << "Printing backward: ";
    dlist.printBackward();
    dlist.removeHead();
    dlist.removeTail();
    dlist.removeNode(dlist.head->next); std::cout << std::endl;
    std::cout << "Double Linked List size after removals: " << dlist.size() << std::endl;
    dlist.printForward();
    dlist.printBackward(); std::cout << std::endl;

    // Test Stack
    std::cout << "--- Stack Test ---" << std::endl;
    Stack<int> stack;
    std::cout << "Stack is empty: " << (stack.isEmpty()  ? "true" : "false") << std::endl ;

    stack.push(4);
    stack.push(2);
    stack.push(3);
    stack.push(20);
    std::cout << "Peek:";
    stack.peek();
    std::cout << std::endl;
    std::cout << "Stack size: " << stack.size() << std::endl;
    stack.print();
    stack.pop();
    std::cout << "Stack size after pop: " << stack.size() << std::endl;
    stack.print();
    std::cout << std::endl;

    // Test Queue
    std::cout << "--- Queue Test ---" << std::endl;
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << "Queue front: "; queue.peek(); std::cout << std::endl;
    std::cout << "Queue size: " << queue.size() << std::endl;
    queue.print();
    queue.dequeue();
    std::cout << "Queue front after dequeue: "; queue.peek(); std::cout << std::endl;
    std::cout << "Queue size after dequeue: " << queue.size() << std::endl;
    queue.print();

    return 0;
}