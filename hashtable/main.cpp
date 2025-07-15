#include "hashtable.hpp"

#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

int main()
{
    HashTable<int, int> hashTable;

    int N;
    std::cin >> N;
    getchar();

    std::string line, command;
    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        std::istringstream iss{line};
        iss >> command;

        int key, value;
        if (command == "insert") {
            iss >> key >> value;
            hashTable.insert(key, value);
        } else if (command == "erase") {
            iss >> key;
            if (hashTable.size()) {
                hashTable.erase(key);
            }
        } else if (command == "find") {
            iss >> key;
            if (hashTable.size()) {
                int* res = hashTable.find(key);
                if (res) {
                    std::cout << *res << std::endl;
                } else {
                    std::cout << "not exist" << std::endl;
                }
            }
        } else if (command == "print") {
            if (hashTable.size())   hashTable.print();
            else                    std::cout << "empty" << std::endl;
        } else if (command == "size") {
            std::cout << hashTable.size() << std::endl;
        } else if (command == "clear") {
            hashTable.clear();
        }
    }
    return 0;
}
