
#pragma once

#include <stdexcept>

template <typename T>
class Vector
{
private:
    T *elements;
    size_t capacity;
    size_t size;

public:
    Vector() : elements{nullptr}, capacity{32}, size{0} {
        elements = new T[capacity];
    }

    ~Vector()
    {
        if (elements)   delete[] elements;
    }

    Vector(const Vector& other) : elements{nullptr}, capacity{other.capacity}, size{other.size}
    {
        if (other.elements) {
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
    }

    Vector& operator=(const Vector& other)
    {
        if (elements) {
            delete[] elements;
            elements = nullptr;
        }
        capacity = other.capacity;
        size = other.size;
        if (other.elements) {
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
        return *this;
    }

    Vector(Vector&& other) : elements{other.elements}, capacity{other.capacity}, size{other.size}
    {
        other.elements = nullptr;
    }

    Vector& operator=(Vector&& other)
    {
        if (elements)   delete[] elements;
        capacity = other.capacity;
        size = other.size;
        elements = other.elements;
        other.elements = nullptr;
        return *this;
    }

    void push_back(const T& value)
    {
        if (size == capacity) {
            reserve(capacity == 0 ? 32 : capacity << 1);
        }
        elements[size++] = value;
    }

    size_t getSize() const
    {
        return size;
    }

    size_t getCapacity() const
    {
        return capacity;
    }

    T& operator[](const size_t index)
    {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    const T& operator[](const size_t index) const
    {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    void insert(size_t index, const T& value)
    {
        if (index > size)  throw std::out_of_range("insert index is out-of-range!\n");
        if (size == capacity)   reserve(capacity == 0 ? 32 : capacity << 1);
        for (size_t i = size; i > index; --i)   elements[i] = elements[i - 1];
        elements[index] = value;
        ++size;
    }

    void pop_back()
    {
        if (size > 0)   --size;
    }

    void clear()
    {
        size = 0;
    }

    T* begin()
    {
        return elements;
    }

    T* end()
    {
        return elements + size;
    }

    const T* begin() const
    {
        return elements;
    }

    const T* end() const
    {
        return elements + size;
    }

    void printElements() const
    {
        for (size_t i = 0; i < size; ++i)   std::cout << elements[i] << " ";
        std::cout << std::endl;
    }

private:
    void reserve(const size_t nCapacity)
    {
        if (nCapacity > capacity) {
            T* nelements = new T[nCapacity];
            std::copy(elements, elements + size, nelements);
            delete[] elements;
            capacity = nCapacity;
            elements = nelements;
        }
    }

};

