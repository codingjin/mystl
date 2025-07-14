#pragma once
#include <stdexcept>

template <typename T>
class Deque {
private:
    T* elements;
    size_t capacity;
    size_t frontIndex;
    size_t backIndex;
    size_t size;

public:
    Deque() : elements{nullptr}, capacity{0}, frontIndex{0}, backIndex{0}, size{0} {}

    ~Deque()
    {
        if (elements)   delete[] elements;
    }

    void push_front(const T& value)
    {
        if (size == capacity)   resize();

        frontIndex = (frontIndex -1 + capacity) % capacity;

        elements[frontIndex] = value;

        ++size;
    }

    void push_back(const T& value)
    {
        if (size == capacity)   resize();

        elements[backIndex] = value;

        backIndex = (backIndex + 1) % capacity;

        ++size;
    }

    void pop_front()
    {
        if (size == 0)  throw std::out_of_range("Deque is empty");
        frontIndex = (frontIndex + 1) % capacity;
        --size;
    }

    void pop_back()
    {
        if (size == 0)  throw std::out_of_range("Deque is empty");
        backIndex = (backIndex - 1 + capacity) % capacity;
        --size;
    }

    T& operator[](const int index)
    {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range!\n");
        return elements[(frontIndex + index) % capacity];
    }

    size_t getSize() const
    {
        return size;
    }

    void clear()
    {
        while (size)
            pop_front();
    }

    void printElements() const
    {
        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[(index + i) % capacity] << " ";
        }
        std::cout << std::endl;
    }

private:
    void resize()
    {
        size_t newCapacity = (capacity == 0) ? 1 : capacity << 1;

        T* newElements = new T[newCapacity];

        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[index];
            index = (index + 1) % capacity;
        }

        if (elements)   delete[] elements;
        elements = newElements;
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = size;
    }
};






