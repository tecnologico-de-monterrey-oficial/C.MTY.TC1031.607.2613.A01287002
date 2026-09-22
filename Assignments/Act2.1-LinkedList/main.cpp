#include <iostream>
#include "helper.h"
#include <memory>
#include "linkedlist.h"

int main() {
    // int x = 42;
    // int* ptr = &x;

    // std::cout << "Value of x: " << x << std::endl;
    // std::cout << "Address of x: " << ptr << std::endl;

    // int* q = new int(4);
    // std::cout << "Value of q: " << q << std::endl;
    // std::cout << "Value of q: " << *q << std::endl;
    // delete q;
    // std::cout << "Value of q: " << q << std::endl;
    // std::cout << "Value of q: " << *q << std::endl;
    
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.prepend(0);
    list.print();

    std::unique_ptr<Fraction> f = std::make_unique<Fraction>(3, 4);
    f->print();
    f.reset(new Fraction(5, 6));
    f->print();

    std::shared_ptr<Fraction> f1 = std::make_shared<Fraction>(7, 8);
    f1->print();
    std::cout << f1 << std::endl;
    std::shared_ptr<Fraction> f2 = f1;
    f2->print();
    std::cout << f2 << std::endl;
}