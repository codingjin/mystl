
#include <iostream>
#include <sstream>
#include <string>

#include "deque.hpp"

int main()
{
    Deque<int> myDeque;
    
    int N;
    std::cin >> N;
    getchar();

    std::string line;
    std::string command;
    int value;

    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        iss >> command;

        if (command == "push_back") {
            iss >> value;
            myDeque.push_back(value);
        } else if (command == "push_front") {
            iss >> value;
            myDeque.push_front(value);
        } else if (command == "pop_back") {
            if (myDeque.getSize()) myDeque.pop_back();
        } else if (command == "pop_front") {
            if (myDeque.getSize()) myDeque.pop_front();
        } else if (command == "clear") {
            myDeque.clear();
        } else if (command == "size") {
            std::cout << myDeque.getSize() << std::endl;
        } else if (command == "get") {
            iss >> value;
            std::cout << myDeque[value] << std::endl;
        } else if (command == "print") {
            if (myDeque.getSize())  myDeque.printElements();
            else                    std::cout << "empty" << std::endl;
        }
    }
    return 0;
}