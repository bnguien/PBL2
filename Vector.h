#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iostream>

template <typename T>
class vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void realloc(size_t newCapacity);

public:
    // Constructors
    vector();
    vector(size_t n);
    vector(size_t n, const T& value);
    vector(std::initializer_list<T> list);
    vector(const vector<T>& other);
    vector(vector<T>&& other) noexcept;
    ~vector();

    // Assignment operators
    vector<T>& operator=(const vector<T>& other);
    vector<T>& operator=(vector<T>&& other) noexcept;
    vector<T>& operator=(std::initializer_list<T> list);

    // Element access
    T& at(size_t pos);
    const T& at(size_t pos) const;
    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T* data() noexcept;
    const T* data() const noexcept;
    T& get(size_t index);
    const T& get(size_t index) const;

    // Iterators
    T* begin() noexcept;
    const T* begin() const noexcept;
    T* end() noexcept;
    const T* end() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    void reserve(size_t new_cap);
    void shrink_to_fit();

    // Modifiers
    void clear() noexcept;
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void resize(size_t count);
    void resize(size_t count, const T& value);
    
    // Print function
    void print() const;
};

#include "Vector.cpp"

#endif // VECTOR_H
