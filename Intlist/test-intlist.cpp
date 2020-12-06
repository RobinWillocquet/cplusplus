#include <iostream>
#include "intlist.h"

int main(){
    IntList l;
    l.add_front(2);
    l.print();
    l.add_front(1);
    l.add_back(3);
    l.print();
    l.remove_front();
    l.print();
    l.remove_back();
    l.print();
    std::cout << std::boolalpha << l.search(2) << std::endl;
    std::cout << std::boolalpha << l.search(3) << std::endl;
    l.add_front(20);
    l.print();
    l.add_back(30);
    l.print();
    l.remove(2);
    l.print();
    return 0;
}