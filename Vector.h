#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template <typename T>
class vector
{
private:
    T *data;
    size_t size_;
    size_t capacity_;

    void resize(size_t newCapacity);

public:
    vector();
    vector(const T *array, size_t n);
    vector(size_t n, const T &value);
    vector(std::initializer_list<T> list);
    ~vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void push_back(const T &value);
    void pop_back();
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    T &get(size_t index);
    const T &get(size_t index) const;

    T *begin();
    T *end();
    const T *begin() const;
    const T *end() const;
    void clear();
};

#include "Vector.cpp"

#endif
