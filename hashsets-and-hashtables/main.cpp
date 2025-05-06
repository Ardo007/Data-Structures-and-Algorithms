#include <iostream>
#include "hashset.cpp"

int main() {

    HashSet h;

    h.insert(4);

    std::cout << h.contains(4);
    
    return 0;
}