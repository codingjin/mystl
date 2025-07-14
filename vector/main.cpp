#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstddef>

#include "vector.hpp"

/*
15
push 20
push 30
push 40
print
insert 0 10
size
print
get 1
pop
print
iterator
foreach
clear
size
print
*/


int main()
{
    Vector<int> myVector;

    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        std::istringstream iss{line};
        std::string command;
        iss >> command;
        //std::cout << "Get command: " << command << std::endl;

        if (command == "push") {
            int value;
            iss >> value;
            //std::cout << "value get: " << value << std::endl;
            myVector.push_back(value);
        } else if (command == "print") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            myVector.printElements();
        } else if (command == "size") {
            std::cout << myVector.getSize() << std::endl;
        } else if (command == "get") {
            int index;
            iss >> index;
            std::cout << myVector[index] << std::endl;
        } else if (command == "insert") {
            int index, value;
            iss >> index >> value;
            myVector.insert(index, value);
        } else if (command == "pop") {
            myVector.pop_back();
        } else if (command == "iterator") {
            size_t size = myVector.getSize();
            if (size == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }

            for (auto it = myVector.begin(); it != myVector.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        } else if (command == "foreach") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto& e : myVector) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        } else if (command == "clear") {
            myVector.clear();
        }

    }
    return 0;
}