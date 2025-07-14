#pragma once

#include <stdexcept>

template <typename T>
class List
{
public:
    template <typename L>
    friend std::ostream& operator<<(std::ostream& os, const List<L>& pt);

private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr) : data{value}, next{nextNode}, prev{prevNode} {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    List() : head{nullptr}, tail{nullptr}, size{0} {}

    void clear()
    {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    ~List()
    {
        clear();
    }

    void push_back(const T& value)
    {
        Node* newnode = new Node{value, nullptr, tail};
        if (tail)   tail->next = newnode;
        else        head = newnode;
        tail = newnode;
        ++size;
    }

    void push_front(const T& value)
    {
        Node* newnode = new Node{value, head, nullptr};
        if (head) {
            head->prev = newnode;
            head = newnode;
        } else {
            head = newnode;
            tail = newnode;
        }
        ++size;
    }

    size_t getSize() const { return size; }

    T& operator[](const size_t index)
    {
        if (index >= size)  throw std::out_of_range("Index out-of-range!\n");
        Node* current = head;
        for (size_t i = 0; i < index; ++i)  current = current->next;
        return current->data;
    }

    const T& operator[](const size_t index) const
    {
        if (index >= size)  throw std::out_of_range("Index out-of-range!\n");
        Node* current = head;
        for (size_t i = 0; i < index; ++i)  current = current->next;
        return current->data;
    }

    void pop_back()
    {
        if (size > 0) {
            if (size == 1) {
                delete head;
                head = nullptr;
                tail = nullptr;
            } else {
                Node* current = tail;
                tail = tail->prev;
                tail->next = nullptr;
                delete current;
            }
            --size;
        }
    }

    void pop_front()
    {
        if (size > 0) {
            if (size == 1) {
                delete head;
                head = nullptr;
                tail = nullptr;
            } else {
                Node* current = head;
                head->next->prev = nullptr;
                head = head->next;
                delete current;
            }
            --size;
        }
    }

    Node* getNode(const T& value)
    {
        Node* current = head;
        while (current) {
            if (current->data == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    T* find(const T& value)
    {
        Node* node = getNode(value);
        if (node)   return node->data;
        else        return nullptr;
    }

    void remove(const T& value)
    {
        if (size > 0) {
            Node* current = head;
            while (current) {
                if (current->data == value) {
                    if (current->prev == nullptr && current->next == nullptr) {
                        head = nullptr;
                        tail = nullptr;
                    } else if (current->prev == nullptr && current->next) {
                        current->next->prev = nullptr;
                        head = current->next;
                    } else if (current->prev && current->next == nullptr) {
                        current->prev->next = nullptr;
                        tail = current->prev;
                    } else { // current is a middle node, which has prev and next non-empty nodes 
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                    }
                    delete current;
                    current = nullptr;
                    --size;
                    return;
                }
                current = current->next;
            }
        }
    }

    bool empty() const { return size == 0; }

    Node* begin() { return head; }
    Node* end() {return nullptr; }

    const Node* begin() const { return head; }
    const Node* end() const { return nullptr; }

    void printElements() const
    {
        for (Node *current = head; current; current = current->next) {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& pt)
{
    for (typename List<T>::Node* current = pt.head; current; current = current->next) {
        os << " " << current->data;
    }
    os << std::endl;
    return os;
}

